//
// Created by 竹内 直 on 2018/03/06.
//

#ifndef WEBSERVER_HTTPRESPONSEGET_H
#define WEBSERVER_HTTPRESPONSEGET_H


#include <string>
#include "HttpResponseBase.h"

class HttpResponseGet : public HttpResponseBase {
public:
    HttpResponseGet(int sockfd);
    size_t response(char* uri) override;
};


#endif //WEBSERVER_HTTPRESPONSEGET_H
