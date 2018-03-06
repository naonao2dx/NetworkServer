//
// Created by 竹内 直 on 2018/03/06.
//

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include "HttpResponseHead.h"

HttpResponseHead::HttpResponseHead(int sockfd)
        : HttpResponseBase(sockfd)
{

}

int HttpResponseHead::response(char* uri) {
    int len;
    /*
    int readfd;

    char reqfile[256];
    char openfile[256];
    char docroot[256];

    if (m_uri[0] == '\0') {
        strcat(reqfile, "index.html");
    }

    strcat(openfile, docroot);
    strcat(openfile, reqfile);

    if ( (readfd = open(openfile, O_RDONLY)) == -1) {
        addResponse(m_sockfd, "HTTP/1.1 404 Not Found \r\n");
        addResponse(m_sockfd, "Server: WebServer\r\n");
        addResponse(m_sockfd, "\r\n");
    } else {
        addResponse(m_sockfd, "HTTP/1.1 200 OK \r\n");
        addResponse(m_sockfd, "Server: WebServer\r\n");
        addResponse(m_sockfd, "\r\n");
    }
    close(readfd);*/

    return len;
}