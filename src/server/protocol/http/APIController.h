//
// Created by 竹内 直 on 2018/03/12.
//

#ifndef NETWORKSERVER_APICONTROLLER_H
#define NETWORKSERVER_APICONTROLLER_H


#include "HttpController.h"

class APIController : public HttpController{
public:
    APIController(int connfd, struct sockaddr* cliaddr);

    void setStatusCode() override;
    void responseBody() override;
};


#endif //NETWORKSERVER_APICONTROLLER_H
