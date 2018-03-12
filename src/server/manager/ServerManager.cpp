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
        m_serverArray.push_back(webServer);
        webServer->start();
    } else {
        std::cerr << "No such server";
        std::exit(EXIT_FAILURE);
    }
}

void ServerManager::destructServer() {
    std::cout << "Destruct Server" << std::endl;

    // Kill all child process
    for (auto itr = std::begin(m_serverArray); itr != std::end(m_serverArray); ++itr) {
        (**itr).killChild();

    }
}

void ServerManager::sigInt(int signo) {
    auto serverManager = ServerManager::getInstance();
    serverManager->destructServer();
}

