//
// Created by 竹内 直 on 2018/03/02.
//

#include "GameServer.h"
#include "../common/protocol/TCP.h"
#include "../common/system/Signal.h"
#include "../common/system/LockFcntl.h"
#include "../common/protocol/Http.h"
#include "ServerManager.h"
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <iostream>

GameServer::GameServer(int listenPort, int childProcessNum):
m_listenPort(listenPort),
m_childProcessNum(childProcessNum)
{
    m_pLockFcntl = LockFcntl::getInstance();
}

void GameServer::start() {
    int listenfd, i;
    socklen_t addrlen;
    std::string strListenPort = std::to_string(m_listenPort);

    listenfd = TCP::listen(nullptr, strListenPort.c_str(), &addrlen);
    m_pids.reset(new pid_t[m_childProcessNum]);

    m_pLockFcntl->init(std::string("./GameServer.lock"));

    for (i = 0; i < m_childProcessNum; i++)
        m_pids[i] = makeChild(i, listenfd, addrlen);
    Signal::Handle(SIGTERM, ServerManager::sigInt);
    Signal::Handle(SIGINT, ServerManager::sigInt);

    for ( ; ; )
        pause();
}

pid_t GameServer::makeChild(int i, int listenfd, int addrlen) {
    pid_t pid;
    if ( (pid = fork()) > 0) {
        std::cout << "fork process: " << pid << std::endl;
        return pid;
    }
    process(i, listenfd, addrlen);
    return pid;
}

void GameServer::process(int i, int listenfd, int addrlen) {
    int connfd;
    socklen_t clilen;
    struct sockaddr *cliaddr;
    cliaddr = new struct sockaddr;

    for ( ; ; ) {
        clilen = addrlen;

        m_pLockFcntl->wait();
        connfd = accept(listenfd, cliaddr, &clilen);
        std::cout << "accept process: " << getpid() << std::endl;
        m_pLockFcntl->release();
        Http::process(connfd);

        close(connfd);

    }
}

void GameServer::killChild() {
    int i;
    for (i = 0; i < m_childProcessNum; i++) {
        kill(m_pids[i], SIGTERM);
        std::cout << "kill process: " << m_pids[i] << std::endl;
    }

    while (wait(NULL) > 0)
        ;
    if(errno != ECHILD)
        std::cerr << "Wait error" << std::endl;
    exit(0);
}