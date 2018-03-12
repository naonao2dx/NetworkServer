//
// Created by 竹内 直 on 2018/03/02.
//

#ifndef WEBSERVER_WEBSERVER_H
#define WEBSERVER_WEBSERVER_H

#include <sys/socket.h>
#include <string>
#include <vector>
#include "../../common/system/Lock.h"
#include "../../common/system/LockFcntl.h"
#include "../../common/system/LockPthread.h"
#include "../AbstractServer.h"
#include <sys/wait.h>


class WebServer : public AbstractServer {
public:
    WebServer(){};
    WebServer(std::string strExec);

    std::shared_ptr<Lock> m_pLock;

    void start() override;
    void killChild() override;

    std::string m_strExec;

private:
    int m_listenPort; // リスニングポート
    int m_startServer; // preforkのプロセス数
    std::vector<pid_t> m_pids; // 子プロセスのpid配列

    pid_t makeChild(int i, int listenfd, int addrlen);
    void process(int i, int listenfd, int addrlen);

};


#endif //WEBSERVER_WEBSERVER_H
