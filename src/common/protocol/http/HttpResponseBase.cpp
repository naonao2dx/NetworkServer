//
// Created by 竹内 直 on 2018/03/06.
//
#include <unistd.h>
#include <iostream>
#include <sstream>
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
    headerRow1Array.emplace_back("HTTP/1.1");
    headerRow1Array.push_back(std::to_string(httpStatusCode));
    headerRow1Array.push_back(statusStr);
    std::string headerRow1Str = StrUtil::implode(headerRow1Array, " ");
    addResponse(m_sockfd, headerRow1Str.c_str());

    headerStr += "\r\n";
    headerStr += "Server: WebServer\r\n\r\n";
    addResponse(m_sockfd, headerStr.c_str());
}

size_t HttpResponseBase::response(char* uri, std::vector<std::string> &logStrArray) {
    setResponseHeader(405);
    logStrArray.push_back("405");
}

size_t HttpResponseBase::addResponse(int fd, const char *message) {
    size_t len;
    len = strlen(message);
    if (write(fd, message, len) != len) {

    }
    return len;
}