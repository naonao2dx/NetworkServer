//
// Created by 竹内 直 on 2018/03/06.
//

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include "HttpResponseHead.h"

HttpResponseHead::HttpResponseHead(int sockfd)
        : HttpResponseBase(sockfd)
{

}

size_t HttpResponseHead::response(char* uri, std::vector<std::string> &logStrArray) {
    int readfd;
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
    logStrArray.push_back(std::to_string(httpStatusCode));
}