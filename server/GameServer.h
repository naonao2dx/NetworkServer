//
// Created by 竹内 直 on 2018/03/02.
//

#ifndef WEBSERVER_GAMESERVER_H
#define WEBSERVER_GAMESERVER_H

#include <sys/socket.h>
#include <string>
#include "../common/system/LockFcntl.h"


class GameServer {
public:
    LockFcntl *m_pLockFcntl;

    static GameServer* getInstance();
    void start();

private:
    static GameServer *s_pInstance;

    GameServer();
    virtual ~GameServer(){}

    std::string m_listenPort = "8080";
    int nchildren = 10;
    pid_t *m_pids;

    static void sigInt(int signo);
    pid_t makeChild(int i, int listenfd, int addrlen);
    void process(int i, int listenfd, int addrlen);
    void killChild();

};


#endif //WEBSERVER_GAMESERVER_H
