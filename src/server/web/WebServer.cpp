//
// Created by 竹内 直 on 2018/03/02.
//

#include "WebServer.h"
#include "../protocol/tcp/TCP.h"
#include "../config/Config.h"
#include "../../common/system/Signal.h"
#include "../manager/ServerManager.h"
#include "../protocol/http/HttpController.h"
#include "../protocol/http/APIController.h"
#include <unistd.h>
#include <netinet/in.h>


WebServer::WebServer(std::string strExec)
: _strExec(strExec)
{
#ifdef __APPLE__
    // Can't use mutex lock over multi process at MacOS (PTHREAD_PROCESS_SHARED)
    _pLock = LockFcntl::getInstance();
#else
    //_pLock = LockPthread::getInstance();
    _pLock = LockFcntl::getInstance();
#endif
    auto config = Config::getInstance();
    std::string listeningPort = config->getConfigValue(_strExec, "ListenPort");
    std::string startServer = config->getConfigValue(_strExec, "StartServer");
    _listenPort = std::stoi(listeningPort);
    _startServer = std::stoi(startServer);
}

void WebServer::start() {
    int listenfd;
    socklen_t addrlen;
    std::string strListenPort = std::to_string(_listenPort);

    listenfd = TCP::Listen(nullptr, strListenPort.c_str(), &addrlen);

    _pLock->init();

    for (auto i = 0; i < _startServer; i++)
        _pids.push_back(makeChild(i, listenfd, addrlen));

    // Register SIGINT and SIGTERM function to kill all child process when receive signals
    Signal::Handle(SIGTERM, ServerManager::sigInt);
    Signal::Handle(SIGINT, ServerManager::sigInt);

    // Parent process is paused
    for ( ; ; )
        pause();
}

pid_t WebServer::makeChild(int i, int listenfd, int addrlen) {
    pid_t pid;
    if ( (pid = fork()) > 0) {
        std::cout << "fork process: " << pid << std::endl;
        return pid;
    }
    // Child process
    process(i, listenfd, addrlen);
    return pid;
}

void WebServer::process(int i, int listenfd, int addrlen) {
    int connfd;
    socklen_t clilen;
    struct sockaddr *cliaddr;
    cliaddr = new struct sockaddr;

    auto config = Config::getInstance();
    std::string accesslogFilePath = config->getConfigValue(_strExec, "AccessLogFilePath");
    std::ofstream accesslog(accesslogFilePath, std::ios::out | std::ios::app);
    if (!accesslog) {
        std::cerr << "Could not file open: " << accesslogFilePath << std::endl;
        std::exit(EXIT_FAILURE);
    }

    for ( ; ; ) {
        std::unique_ptr<HttpController> httpController;

        clilen = addrlen;
        _pLock->wait();
        connfd = accept(listenfd, cliaddr, &clilen);
        _pLock->release();

        if ("Web" == _strExec) {
            httpController.reset(new HttpController(connfd, cliaddr));
        } else if ("API" == _strExec) {
            httpController.reset(new APIController(connfd, cliaddr));
        }
        httpController->process();
        close(connfd);

        httpController->outputAccessLog(accesslog);

    }
}

void WebServer::killChild() {
    for (auto i = 0; i < _startServer; i++) {
        kill(_pids.at(i), SIGTERM);
        std::cout << "kill process: " << _pids.at(i) << std::endl;
    }

    while (wait(nullptr) > 0)
        ;
    if(errno != ECHILD)
        std::cerr << "Wait error" << std::endl;
    exit(0);
}