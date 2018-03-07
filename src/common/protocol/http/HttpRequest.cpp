//
// Created by admin on 2018/03/04.
//

#include <unistd.h>
#include <iostream>
#include <sstream>
#include "HttpRequest.h"

#include "../../code/StrUtil.h"
#include "../../code/TimeUtil.h"

HttpMethod HttpRequest::process(int sockfd, char* uri, std::vector<std::string> &logStrArray) {
    char buf[1024];
    char method[16];
    char httpver[64];
    HttpMethod enumMethod;

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

    logStrArray.push_back(TimeUtil::getNow());
    logStrArray.push_back(method);
    logStrArray.push_back(uri);

    return enumMethod;
}