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
    HttpController();
    HttpController(int connfd, struct sockaddr* cliaddr);

    // Request model class
    HttpRequest m_httpRequest;

    // Response model class
    HttpResponse m_httpResponse;

    void process();
    void outputAccessLog(std::ofstream &accessLog);

private:
    // Connection socket descriptor
    int m_connfd;

    // File descriptor
    int m_readfd;

    void request();
    void setStatusCode();
    void responseHeader();
    void responseBody();

    size_t addResponse(int fd, const char *message, size_t len = 0);

    // Status code
    std::map<int, std::string> httpStatusCodeMap {
            {200, "OK"},
            {404, "Not Found"},
            {405, "Method Not Allowed"}
    };

    // Acceptable method set
    std::set<std::string> m_enableMethodSet = {"HEAD", "GET", "POST"};

};


#endif //NETWORKSERVER_HTTPCONTROLLER_H
