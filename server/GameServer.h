//
// Created by 竹内 直 on 2018/03/02.
//

#ifndef WEBSERVER_GAMESERVER_H
#define WEBSERVER_GAMESERVER_H

#include <sys/socket.h>
#include <string>
#include "../common/system/LockFcntl.h"
#include "AbstractServer.h"


class GameServer : public AbstractServer {
public:
    GameServer(int listenPort, int childProcessNum);
    GameServer(const GameServer &rhs);
    virtual ~GameServer(){};

    LockFcntl *m_pLockFcntl;

    void start();
    void killChild();

private:
    int m_listenPort;
    int m_childProcessNum;
    pid_t *m_pids;

    pid_t makeChild(int i, int listenfd, int addrlen);
    void process(int i, int listenfd, int addrlen);

};


#endif //WEBSERVER_GAMESERVER_H