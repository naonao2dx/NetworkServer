//
// Created by 竹内 直 on 2018/03/02.
//

#include <new>
#include <iostream>
#include "ServerManager.h"
#include "GameServer.h"
#include "../common/system/Signal.h"

ServerManager *ServerManager::s_pInstance = nullptr;

ServerManager* ServerManager::getInstance() {
    if (nullptr == s_pInstance) {
        try {
            s_pInstance = new ServerManager();
        } catch (std::bad_alloc& r) {
            std::cerr << r.what() << std::endl;
        }
    }
    return s_pInstance;
}

void ServerManager::constructServer() {
    std::cout << "Construct Server" << std::endl;
    std::shared_ptr<AbstractServer> gmServer = std::make_shared<GameServer>(8080, 10);
    m_serverArray.push_back(gmServer);
    gmServer->start();
}

void ServerManager::destructServer() {
    std::cout << "Destruct Server" << std::endl;
    for (auto itr = std::begin(m_serverArray); itr != std::end(m_serverArray); ++itr) {
        (**itr).killChild();

    }
}

void ServerManager::sigInt(int signo) {
    ServerManager *serverManager = ServerManager::getInstance();
    serverManager->destructServer();
}

