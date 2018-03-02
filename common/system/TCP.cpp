//
// Created by 竹内 直 on 2018/03/02.
//

#include <netdb.h>
#include <strings.h>
#include <iostream>
#include <unistd.h>
#include "TCP.h"

int TCP::listen(const char *host, const char *serv, socklen_t *addrlenp) {
    int listenfd, n;
    struct addrinfo hints, *res, *ressave;
    const int on = 1;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
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
    } while ( (res = res->ai_next) != NULL);

    if (nullptr == res) {
        std::cerr << "TCP Listen error for " << host << ", " << serv << std::endl;
    }
    ::listen(listenfd, LISTENQ);

    if (addrlenp)
        *addrlenp = res->ai_addrlen;
    freeaddrinfo(ressave);

    return (listenfd);
}
