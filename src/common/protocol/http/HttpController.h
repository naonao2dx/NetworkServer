//
// Created by 竹内 直 on 2018/03/08.
//

#ifndef NETWORKSERVER_HTTPCONTROLLER_H
#define NETWORKSERVER_HTTPCONTROLLER_H

#include <string>
#include <map>
#include <fstream>

enum HttpMethod {
    HEAD,
    GET,
    POST,
    OTHER,
};

class HttpController {
public:
    HttpController();
    HttpController(int connfd, struct sockaddr* cliaddr);

    void process();
    void outputAccessLog(std::ofstream &accessLog);

private:
    int m_connfd;
    int m_readfd;
    std::string m_uri;
    std::string m_returi;
    std::string m_httpver;
    std::string m_methodStr;
    std::string m_remoteIp;
    int m_remotePort;
    HttpMethod m_method;
    int m_statusCode;
    std::string m_iptype;
    std::string m_userAgent;

    void request();
    void setStatusCode();
    void responseHeader();
    void responseBody();

    size_t addResponse(int fd, const char *message, size_t len = 0);

    std::map<int, std::string> httpStatusCodeMap {
            {200, "OK"},
            {404, "Not Found"},
            {405, "Method Not Allowed"}
    };

};


#endif //NETWORKSERVER_HTTPCONTROLLER_H
