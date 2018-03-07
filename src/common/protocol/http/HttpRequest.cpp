//
// Created by admin on 2018/03/04.
//

#include <unistd.h>
#include <iostream>
#include "HttpRequest.h"
#include "HttpResponseBase.h"

HttpMethod HttpRequest::process(int sockfd, char* uri) {
    char buf[1024];
    char method[16];
    char httpver[64];
    HttpMethod enumMethod;
    std::unique_ptr<HttpResponseBase> httpResponse;

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



    return enumMethod;
}