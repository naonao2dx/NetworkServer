//
// Created by 竹内 直 on 2018/03/02.
//

#ifndef WEBSERVER_SERVERMANAGER_H
#define WEBSERVER_SERVERMANAGER_H


#include <vector>
#include "AbstractServer.h"
#include "../common/code/Singleton.h"

class ServerManager : public Singleton<ServerManager> {
private:
    friend class Singleton<ServerManager>;
    ServerManager() {};
public:
    static void sigInt(int signo);

    void constructServer();
    void destructServer();

    std::vector<std::shared_ptr<AbstractServer>> m_serverArray;

protected:

};


#endif //WEBSERVER_SERVERMANAGER_H
