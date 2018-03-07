//
// Created by admin on 2018/03/04.
//

#include <unistd.h>
#include <iostream>
#include <sstream>
#include "HttpRequest.h"

#include "../../code/StrUtil.h"
#include "../../code/TimeUtil.h"

HttpMethod HttpRequest::process(int sockfd, char* uri, std::ofstream& accesslog) {
    char buf[1024];
    char method[16];
    char httpver[64];
    HttpMethod enumMethod;
    std::vector<std::string> logStrArray;

    if (read(sockfd, buf, 1024) <= 0) {
        exit(1);
    }

    sscanf(buf, "%s %s %s", method, uri, httpver);

    if (strcmp(method, "HEAD") == 0) {
        enumMethod = HEAD;
    } else if (strcmp(method, "GET") == 0) {
        enumMethod = GET;
    } else if (strcmp(method, "POST") == 0) {
        enumMethod = POST;
    } else {
        enumMethod = OTHER;
    }

    accesslog << TimeUtil::getNow() << " ";
    logStrArray.emplace_back(method);
    logStrArray.emplace_back(uri);
    accesslog << StrUtil::implode(logStrArray, " ");

    return enumMethod;
}