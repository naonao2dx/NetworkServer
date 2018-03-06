//
// Created by 竹内 直 on 2018/03/06.
//

#ifndef WEBSERVER_HTTPRESPONSEHEAD_H
#define WEBSERVER_HTTPRESPONSEHEAD_H


#include "HttpResponseBase.h"

class HttpResponseHead : public HttpResponseBase {
public:
    HttpResponseHead(int sockfd);
    virtual int response(char* uri);
};

#endif //WEBSERVER_HTTPRESPONSEHEAD_H
