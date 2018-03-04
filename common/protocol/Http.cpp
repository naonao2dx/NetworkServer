//
// Created by admin on 2018/03/04.
//

#include <unistd.h>
#include <iostream>
#include "Http.h"

void Http::process(int sockfd) {
    int readfd;
    int len;
    char buf[1024];
    char method[16];
    char uri[256];
    char httpver[64];

    if (read(sockfd, buf, 1024) <= 0) {
        return;
    } else {
        sscanf(buf, "%s %s %s", method, uri, httpver);
        std::cout << uri << std::endl;
        response(sockfd, "HTTP/1.1 200 OK\r\n");
        response(sockfd, "Server: bamboo\r\n");
        response(sockfd, "\r\n");
    }



    std::cout << "http" << std::endl;
}


int Http::response(int fd, std::string message) {
    int len;
    len = message.size();
    if (write(fd, message.c_str(), len) != len) {
        std::cout << "write" << std::endl;

    }

    return len;
}