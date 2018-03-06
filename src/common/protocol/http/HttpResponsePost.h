//
// Created by 竹内 直 on 2018/03/06.
//

#ifndef WEBSERVER_HTTPRESPONSEPOST_H
#define WEBSERVER_HTTPRESPONSEPOST_H

#include "HttpResponseBase.h"

class HttpResponsePost : public HttpResponseBase {
public:
    HttpResponsePost(int sockfd);
    virtual int response(char* uri);
};


#endif //WEBSERVER_HTTPRESPONSEPOST_H
