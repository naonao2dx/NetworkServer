//
// Created by 竹内 直 on 2018/03/02.
//

#include "GameServer.h"
#include "../../common/protocol/tcp/TCP.h"
#include "../../common/system/Signal.h"
#include "../../common/protocol/http/HttpRequest.h"
#include "../ServerManager.h"
#include "../../common/protocol/http/HttpResponseHead.h"
#include "../../common/protocol/http/HttpResponseGet.h"
#include "../../common/protocol/http/HttpResponsePost.h"
#include <unistd.h>
#include <cerrno>
#include <iostream>
#include <fstream>
#include <netinet/in.h>
#include <arpa/inet.h>

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

    listenfd = TCP::Listen(nullptr, strListenPort.c_str(), &addrlen);

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
    std::unique_ptr<HttpResponseBase> httpResponse;

    std::ofstream accesslog("../resource/log/GameServer/access.log", std::ios::out | std::ios::app);

    for ( ; ; ) {
        clilen = addrlen;
        char uri[256];

        m_pLock->wait();
        connfd = accept(listenfd, cliaddr, &clilen);
        struct sockaddr_in *test = (struct sockaddr_in *) cliaddr;
        struct in_addr ip = test->sin_addr;
        std::cout << inet_ntoa(ip) << ":";
        std::cout  << test->sin_port << std::endl;
        std::cout << "accept process: " << getpid() << std::endl;
        m_pLock->release();
        HttpMethod method = HttpRequest::process(connfd, uri, accesslog);

        switch(method) {
            case HEAD: {
                httpResponse.reset(new HttpResponseHead(connfd));
                break;
            }
            case GET: {
                httpResponse.reset(new HttpResponseGet(connfd));
                break;
            }
            case POST: {
                httpResponse.reset(new HttpResponsePost(connfd));
                break;
            }
            default: {
                httpResponse.reset(new HttpResponseBase(connfd));
                break;
            }
        }

        httpResponse->response(uri, accesslog);

        accesslog << std::endl;
        close(connfd);

    }
}

void GameServer::killChild() {
    for (auto i = 0; i < m_childProcessNum; i++) {
        kill(m_pids.at(i), SIGTERM);
        std::cout << "kill process: " << m_pids.at(i) << std::endl;
    }

    while (wait(nullptr) > 0)
        ;
    if(errno != ECHILD)
        std::cerr << "Wait error" << std::endl;
    exit(0);
}