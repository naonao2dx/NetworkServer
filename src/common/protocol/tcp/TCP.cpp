//
// Created by 竹内 直 on 2018/03/02.
//

#include <netdb.h>
#include <strings.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "TCP.h"
#include "../http/HttpRequest.h"

int TCP::Listen(const char *host, const char *serv, socklen_t *addrlenp) {
    int listenfd, n;
    struct addrinfo hints, *res, *ressave;
    const int on = 1;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    // ひとまずIPv4固定で
    //hints.ai_family = AF_UNSPEC;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
        std::cerr << "TCP Listen error for " << host << ", " << serv << std::endl;
    ressave = res;

    do {
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenfd < 0)
            continue;

        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;
        close(listenfd);
    } while ( (res = res->ai_next) != nullptr);

    if (nullptr == res) {
        std::cerr << "TCP Listen error for " << host << ", " << serv << std::endl;
    }
    listen(listenfd, LISTENQ);

    if (addrlenp)
        *addrlenp = res->ai_addrlen;
    freeaddrinfo(ressave);

    return (listenfd);
}
