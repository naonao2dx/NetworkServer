//
// Created by 竹内 直 on 2018/03/02.
//

#include <new>
#include <iostream>
#include "ServerManager.h"
#include "GameServer.h"

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
    GameServer *gmServer = GameServer::getInstance();
    gmServer->start();
}