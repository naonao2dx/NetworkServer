//
// Created by 竹内 直 on 2018/03/06.
//

#ifndef WEBSERVER_HTTPRESPONSEBASE_H
#define WEBSERVER_HTTPRESPONSEBASE_H


#include <string>
#include <map>

class HttpResponseBase {
public:
    HttpResponseBase(int sockfd);
    HttpResponseBase() = default;
    virtual int response(char* uri);

protected:
    int m_sockfd;

    void setResponseHeader(int httpStatusCode);
    int addResponse(int fd, const char* message);

    std::map<int, std::string> httpStatusCodeMap {
            {200, "OK"},
            {404, "Not Found"},
            {405, "Method Not Allowed"}
    };
};


#endif //WEBSERVER_HTTPRESPONSEBASE_H