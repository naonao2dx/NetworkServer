//
// Created by admin on 2018/03/04.
//

#ifndef WEBSERVER_HTTPREQUEST_H
#define WEBSERVER_HTTPREQUEST_H


#include <string>
#include <fstream>
#include <vector>

enum HttpMethod {
    HEAD,
    GET,
    POST,
    OTHER,
};

class HttpRequest {
public:
    static HttpMethod process(int sockfd, char* uri, std::vector<std::string> &logStrArray);


};


#endif //WEBSERVER_HTTPREQUEST_H
