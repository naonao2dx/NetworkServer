//
// Created by 竹内 直 on 2018/03/08.
//

#ifndef NETWORKSERVER_HTTPCONTROLLER_H
#define NETWORKSERVER_HTTPCONTROLLER_H

#include <string>
#include <map>
#include <fstream>
#include <set>
#include "HttpRequest.h"
#include "HttpResponse.h"

class HttpController {
public:
    HttpController(int connfd, struct sockaddr* cliaddr);

    // Request model class
    HttpRequest _httpRequest;

    // Response model class
    HttpResponse _httpResponse;

    void process();
    void outputAccessLog(std::ofstream &accessLog);

protected:
    // Connection socket descriptor
    int _connfd;

    // Response file stream
    std::ifstream _ifs;

    void request();
    virtual void setStatusCode();
    void responseHeader();
    virtual void responseBody();

    size_t addResponse(int fd, const char *message, size_t len = 0);

    // Status code
    std::map<int, std::string> httpStatusCodeMap {
            {200, "OK"},
            {404, "Not Found"},
            {405, "Method Not Allowed"}
    };

    // Acceptable method set
    std::set<std::string> _enableMethodSet = {"HEAD", "GET", "POST"};

};


#endif //NETWORKSERVER_HTTPCONTROLLER_H
