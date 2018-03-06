//
// Created by admin on 2018/03/04.
//

#ifndef WEBSERVER_HTTPREQUEST_H
#define WEBSERVER_HTTPREQUEST_H


#include <string>

class HttpRequest {
public:
    static void process(int sockfd);
};


#endif //WEBSERVER_HTTPREQUEST_H
