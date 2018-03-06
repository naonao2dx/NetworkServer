//
// Created by 竹内 直 on 2018/03/06.
//
#include <unistd.h>
#include "HttpResponseBase.h"

HttpResponseBase::HttpResponseBase(int sockfd)
    : m_sockfd(sockfd)
{

}

void HttpResponseBase::setResponseHeader(int httpStatusCode) {
    std::string headerStr;
    std::string statusStr = httpStatusCodeMap[httpStatusCode];

    headerStr.append("HTTP/1.1 ");
    headerStr.append(std::to_string(httpStatusCode).c_str());
    headerStr.append(" ");
    headerStr.append(statusStr.c_str());
    headerStr.append("\r\n");
    headerStr.append("Server: WebServer\r\n");
    headerStr.append("\r\n");
    addResponse(m_sockfd, headerStr.c_str());
}

int HttpResponseBase::response(char* uri) {
    setResponseHeader(405);
}

int HttpResponseBase::addResponse(int fd, const char *message) {
    int len;
    len = strlen(message);
    if (write(fd, message, len) != len) {

    }
    return len;
}