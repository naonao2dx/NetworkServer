//
// Created by 竹内 直 on 2018/03/02.
//

#include "GameServer.h"
#include "../common/protocol/TCP.h"
#include "../common/system/Signal.h"
#include "../common/protocol/HttpRequest.h"
#include "ServerManager.h"
#include <unistd.h>
#include <errno.h>
#include <iostream>

GameServer::GameServer(int listenPort, int childProcessNum):
m_listenPort(listenPort),
m_childProcessNum(childProcessNum)
{
#ifdef __APPLE__
    // Macはプロセスをまたいだmutexロック（PTHREAD_PROCESS_SHARED）が使えない
    m_pLock = LockFcntl::getInstance();
#else
    m_pLock = LockPthread::getInstance();
#endif
}

void GameServer::start() {
    int listenfd;
    socklen_t addrlen;
    std::string strListenPort = std::to_string(m_listenPort);

    listenfd = TCP::listen(nullptr, strListenPort.c_str(), &addrlen);

    m_pLock->init();

    for (auto i = 0; i < m_childProcessNum; i++)
        m_pids.push_back(makeChild(i, listenfd, addrlen));
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

        m_pLock->wait();
        connfd = accept(listenfd, cliaddr, &clilen);
        std::cout << "accept process: " << getpid() << std::endl;
        m_pLock->release();
        HttpRequest::process(connfd);

        close(connfd);

    }
}

void GameServer::killChild() {
    for (auto i = 0; i < m_childProcessNum; i++) {
        kill(m_pids.at(i), SIGTERM);
        std::cout << "kill process: " << m_pids.at(i) << std::endl;
    }

    while (wait(NULL) > 0)
        ;
    if(errno != ECHILD)
        std::cerr << "Wait error" << std::endl;
    exit(0);
}