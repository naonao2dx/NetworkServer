//
// Created by 竹内 直 on 2018/03/02.
//

#include <new>
#include <iostream>
#include "ServerManager.h"
#include "gameserver/GameServer.h"

void ServerManager::constructServer() {
    std::cout << "Construct Server" << std::endl;
    auto gmServer = std::make_shared<GameServer>(8080, 10);
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
    auto serverManager = ServerManager::getInstance();
    serverManager->destructServer();
}

