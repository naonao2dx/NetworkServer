//
// Created by admin on 2018/03/04.
//

#ifndef WEBSERVER_HTTPREQUEST_H
#define WEBSERVER_HTTPREQUEST_H


#include <string>
enum HttpMethod {
    HEAD,
    GET,
    POST,
    OTHER,
};

class HttpRequest {
public:
    static HttpMethod process(int sockfd, char* uri);


};


#endif //WEBSERVER_HTTPREQUEST_H
