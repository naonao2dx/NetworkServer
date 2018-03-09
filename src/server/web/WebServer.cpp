//
// Created by 竹内 直 on 2018/03/02.
//

#include "WebServer.h"
#include "../../common/protocol/tcp/TCP.h"
#include "../../common/system/Signal.h"
#include "../ServerManager.h"
#include "../../common/protocol/http/HttpBase.h"
#include "ConfigWebServer.h"
#include <unistd.h>
#include <iostream>
#include <netinet/in.h>


WebServer::WebServer() {
#ifdef __APPLE__
    // Macはプロセスをまたいだmutexロック（PTHREAD_PROCESS_SHARED）が使えない
    m_pLock = LockFcntl::getInstance();
#else
    m_pLock = LockPthread::getInstance();
#endif

    auto config = ConfigWebServer::getInstance();
    m_listenPort = config->getListeningPort();
    m_startServer = config->getStartServer();
}

void WebServer::start() {
    int listenfd;
    socklen_t addrlen;
    std::string strListenPort = std::to_string(m_listenPort);

    listenfd = TCP::Listen(nullptr, strListenPort.c_str(), &addrlen);

    m_pLock->init();

    for (auto i = 0; i < m_startServer; i++)
        m_pids.push_back(makeChild(i, listenfd, addrlen));
    Signal::Handle(SIGTERM, ServerManager::sigInt);
    Signal::Handle(SIGINT, ServerManager::sigInt);

    for ( ; ; )
        pause();
}

pid_t WebServer::makeChild(int i, int listenfd, int addrlen) {
    pid_t pid;
    if ( (pid = fork()) > 0) {
        std::cout << "fork process: " << pid << std::endl;
        return pid;
    }
    process(i, listenfd, addrlen);
    return pid;
}

void WebServer::process(int i, int listenfd, int addrlen) {
    int connfd;
    socklen_t clilen;
    struct sockaddr *cliaddr;
    cliaddr = new struct sockaddr;

     std::string file3 = "../resource/webserver/log/access3.log";

    auto config = ConfigWebServer::getInstance();
    std::string accesslogFilePath = config->getAccesslogFilePath();
    std::ofstream accesslog(accesslogFilePath, std::ios::out | std::ios::app);
    if (!accesslog) {
        std::cerr << "Could not file open: " << accesslogFilePath << std::endl;
        std::exit(EXIT_FAILURE);
    }

    for ( ; ; ) {
        clilen = addrlen;

        m_pLock->wait();
        connfd = accept(listenfd, cliaddr, &clilen);
        m_pLock->release();

        HttpBase httpBase = HttpBase(connfd, cliaddr);
        httpBase.process();
        httpBase.outputAccessLog(accesslog);

        close(connfd);

    }
}

void WebServer::killChild() {
    for (auto i = 0; i < m_startServer; i++) {
        kill(m_pids.at(i), SIGTERM);
        std::cout << "kill process: " << m_pids.at(i) << std::endl;
    }

    while (wait(nullptr) > 0)
        ;
    if(errno != ECHILD)
        std::cerr << "Wait error" << std::endl;
    exit(0);
}