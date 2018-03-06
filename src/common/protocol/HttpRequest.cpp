//
// Created by admin on 2018/03/04.
//

#include <unistd.h>
#include <iostream>
#include "HttpRequest.h"
#include "HttpResponseBase.h"
#include "HttpResponseGet.h"
#include "HttpResponsePost.h"
#include "HttpResponseHead.h"

void HttpRequest::process(int sockfd) {
    char buf[1024];
    char method[16];
    char uri[256];
    char httpver[64];
    std::unique_ptr<HttpResponseBase> httpResponse;

    if (read(sockfd, buf, 1024) <= 0) {
        return;
    }

    sscanf(buf, "%s %s %s", method, uri, httpver);

    if (strcmp(method, "HEAD") == 0) {
        httpResponse.reset(new HttpResponseHead(sockfd));
    } else if (strcmp(method, "GET") == 0) {
        httpResponse.reset(new HttpResponseGet(sockfd));
    } else if (strcmp(method, "POST") == 0) {
        httpResponse.reset(new HttpResponsePost(sockfd));
    } else {
        httpResponse.reset(new HttpResponseBase(sockfd));
    }

    httpResponse->response(uri);
}