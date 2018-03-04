//
// Created by 竹内 直 on 2018/03/02.
//

#ifndef WEBSERVER_SERVERMANAGER_H
#define WEBSERVER_SERVERMANAGER_H


#include <vector>
#include "AbstractServer.h"

class ServerManager {
public:
    static ServerManager* getInstance();
    static void sigInt(int signo);

    void constructServer();
    void destructServer();

    std::vector<std::shared_ptr<AbstractServer>> m_serverArray;

protected:
    static ServerManager *s_pInstance;
    ServerManager() {};
    virtual ~ServerManager(){};

};


#endif //WEBSERVER_SERVERMANAGER_H
