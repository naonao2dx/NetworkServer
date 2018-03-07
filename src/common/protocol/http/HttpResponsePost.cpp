//
// Created by 竹内 直 on 2018/03/06.
//
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include "HttpResponsePost.h"

HttpResponsePost::HttpResponsePost(int sockfd)
        : HttpResponseBase(sockfd)
{

}

size_t HttpResponsePost::response(char* uri, std::vector<std::string> &logStrArray) {
    size_t len = 0;
    int readfd;
    char buf[1024];

    int httpStatusCode;

    std::string reqfile;
    if (0 == strcmp(uri, "/")) {
        reqfile = "/index.html";
    } else {
        reqfile = uri;
    }

    std::string openfile("../resource/html");
    openfile.append(reqfile);

    if ( (readfd = open(openfile.c_str(), O_RDONLY)) == -1) {
        httpStatusCode = 404;
    } else {
        httpStatusCode = 200;
    }

    setResponseHeader(httpStatusCode);

    if (httpStatusCode == 200) {
        while ( (len = (size_t) read(readfd, buf, 1024)) > 0) {
            if (write(m_sockfd, buf, len) != len) {
                std::cerr << "Error: Writing a response" << std::endl;
                break;
            }
        }
        close(readfd);
    }

    logStrArray.push_back(std::to_string(httpStatusCode));

    return len;
}