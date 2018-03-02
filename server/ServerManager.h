//
// Created by 竹内 直 on 2018/03/02.
//

#ifndef WEBSERVER_SERVERMANAGER_H
#define WEBSERVER_SERVERMANAGER_H


class ServerManager {
public:
    static ServerManager* getInstance();
    void constructServer();
    void destructServer(){};

protected:
    static ServerManager *s_pInstance;
    ServerManager() {};
    virtual ~ServerManager(){};

};


#endif //WEBSERVER_SERVERMANAGER_H
