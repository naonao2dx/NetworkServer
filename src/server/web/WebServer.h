//
// Created by 竹内 直 on 2018/03/02.
//

#ifndef WEBSERVER_HTMLSERVER_H
#define WEBSERVER_HTMLSERVER_H

#include <sys/socket.h>
#include <string>
#include <vector>
#include "../../common/system/LockFcntl.h"
#include "../AbstractServer.h"


class HTMLServer : public AbstractServer {
public:
    HTMLServer(int listenPort, int childProcessNum);
    ~HTMLServer() {};

    std::shared_ptr<Lock> m_pLock;

    void start() override;
    void killChild() override;

private:
    int m_listenPort; // リスニングポート
    int m_childProcessNum; // preforkのプロセス数
    std::vector<pid_t> m_pids; // 子プロセスのpid配列

    pid_t makeChild(int i, int listenfd, int addrlen);
    void process(int i, int listenfd, int addrlen);

};


#endif //WEBSERVER_HTMLSERVER_H
