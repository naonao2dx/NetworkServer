//
// Created by 竹内 直 on 2018/03/06.
//
#include <unistd.h>
#include <vector>
#include "HttpResponseBase.h"
#include "../../code/StrUtil.h"

HttpResponseBase::HttpResponseBase(int sockfd)
    : m_sockfd(sockfd)
{

}

void HttpResponseBase::setResponseHeader(int httpStatusCode) {
    std::string headerStr;
    std::string statusStr = httpStatusCodeMap[httpStatusCode];

    std::vector<std::string> headerRow1Array;
    headerRow1Array.push_back("HTTP/1.1");
    headerRow1Array.push_back(std::to_string(httpStatusCode));
    headerRow1Array.push_back(statusStr);
    std::string headerRow1Str = StrUtil::implode(headerRow1Array, " ");
    addResponse(m_sockfd, headerRow1Str.c_str());

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