//
// Created by 竹内 直 on 2018/03/02.
//

#include <new>
#include <iostream>
#include "ServerManager.h"
#include "../web/WebServer.h"

void ServerManager::constructServer(std::string strExec) {
    std::cout << "Construct Server" << std::endl;
    if ("Web" == strExec || "API" == strExec) {
        auto webServer = std::make_shared<WebServer>(strExec);
        _serverArray.push_back(webServer);
        webServer->start();
    } else {
        std::cerr << "No such server";
        std::exit(EXIT_FAILURE);
    }
}

void ServerManager::destructServer() {
    std::cout << "Destruct Server" << std::endl;

    // Kill all child process
    for (auto itr = std::begin(_serverArray); itr != std::end(_serverArray); ++itr) {
        (**itr).killChild();

    }
}

void ServerManager::sigInt(int signo) {
    auto serverManager = ServerManager::getInstance();
    serverManager->destructServer();
}

