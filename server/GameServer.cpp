//
// Created by 竹内 直 on 2018/03/02.
//

#include "GameServer.h"
#include "../common/system/TCP.h"
#include "../common/system/Signal.h"
#include "../common/system/LockFcntl.h"
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <iostream>

GameServer *GameServer::s_pInstance = nullptr;

GameServer* GameServer::getInstance() {
    if (nullptr == s_pInstance) {
        try {
            s_pInstance = new GameServer();
        } catch (std::bad_alloc& r) {
            std::cerr << r.what() << std::endl;
        }
    }
    return s_pInstance;
}

GameServer::GameServer() {
    m_pLockFcntl = LockFcntl::getInstance();
}

void GameServer::start() {
    int listenfd, i;
    socklen_t addrlen;

    listenfd = TCP::listen(nullptr, m_listenPort.c_str(), &addrlen);
    m_pids = new pid_t[nchildren];
    m_pLockFcntl->init(std::string("./lock.server"));

    for (i = 0; i < nchildren; i++)
        m_pids[i] = makeChild(i, listenfd, addrlen);

    Signal::Handle(SIGTERM, GameServer::sigInt);

    for ( ; ; )
        pause();
}

pid_t GameServer::makeChild(int i, int listenfd, int addrlen) {
    pid_t pid;
    if ( (pid = fork()) > 0) {
        std::cout << "fork pid: " << pid << std::endl;
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
        m_pLockFcntl->release();
        write(connfd, "\"HTTP/1.1 200 OK\\r\\n\\\r\\n\"", strlen("\"HTTP/1.1 200 OK\\r\\n\\\r\\n\""));
        std::cout << "process: " << getpid() << std::endl;

        close(connfd);

    }
}

void GameServer::sigInt(int signo) {
    GameServer* gmServer = GameServer::getInstance();
    gmServer->killChild();
}

void GameServer::killChild() {
    int i;
    for (i = 0; i < nchildren; i++) {
        kill(m_pids[i], SIGTERM);
        std::cout << "kill pid: " << m_pids[i] << std::endl;
    }

    while (wait(NULL) > 0)
        ;
    if(errno != ECHILD)
        std::cerr << "Wait error" << std::endl;
    exit(0);
}