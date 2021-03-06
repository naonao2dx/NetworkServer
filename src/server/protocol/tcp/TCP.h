//
// Created by 竹内 直 on 2018/03/02.
//

#ifndef WEBSERVER_TCP_H
#define WEBSERVER_TCP_H

#include <sys/socket.h>
#include "../../../common/system/LockFcntl.h"

#define LISTENQ   1024

class TCP {
public:
    static int Listen(const char *host, const char *serv, socklen_t *addrlenp);
};


#endif //WEBSERVER_TCP_H
