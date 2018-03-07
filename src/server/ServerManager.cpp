//
// Created by 竹内 直 on 2018/03/02.
//

#include <new>
#include <iostream>
#include "ServerManager.h"
#include "web/WebServer.h"

void ServerManager::constructServer() {
    std::cout << "Construct Server" << std::endl;
    auto webServer = std::make_shared<WebServer>(8080, 10);
    m_serverArray.push_back(webServer);
    webServer->start();
}

void ServerManager::destructServer() {
    std::cout << "Destruct Server" << std::endl;
    for (auto itr = std::begin(m_serverArray); itr != std::end(m_serverArray); ++itr) {
        (**itr).killChild();

    }
}

void ServerManager::sigInt(int signo) {
    auto serverManager = ServerManager::getInstance();
    serverManager->destructServer();
}

