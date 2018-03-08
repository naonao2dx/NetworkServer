//
// Created by 竹内 直 on 2018/03/08.
//

#include "HttpBase.h"
#include "../../code/StrUtil.h"
#include "../../code/TimeUtil.h"
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

HttpBase::HttpBase(int connfd, struct sockaddr* cliaddr) :
m_connfd(connfd)
{
    char ipv6addr[INET6_ADDRSTRLEN];

    // ipaddress
    //struct sockaddr_in *remoteaddr = (struct sockaddr_in *) cliaddr;
    //struct in_addr ipstruct = remoteaddr->sin_addr;
    //m_remoteIp = inet_ntoa(ipstruct);

    // IPv6対応
    struct sockaddr_in6 *remoteaddr6 = (struct sockaddr_in6 *) cliaddr;
    struct in6_addr ipstruct6 = remoteaddr6->sin6_addr;
    inet_ntop(AF_INET6, &remoteaddr6->sin6_addr, ipv6addr, sizeof(ipv6addr));
    m_remoteIp = ipv6addr;

    // port
    m_remotePort = remoteaddr6->sin6_port;
}

void HttpBase::request() {
    char buf[1024];
    char method[10];
    char uri[100];
    char httpver[10];

    if (read(m_connfd, buf, 1024) <= 0) {
        exit(1);
    }

    sscanf(buf, "%s %s %s", method, uri, httpver);

    if (strcmp(method, "HEAD") == 0) {
        m_method = HEAD;
    } else if (strcmp(method, "GET") == 0) {
        m_method = GET;
    } else if (strcmp(method, "POST") == 0) {
        m_method = POST;
    } else {
        m_method = OTHER;
    }

    m_httpver = httpver;
    m_uri = uri;
    m_methodStr = method;
}

void HttpBase::setStatusCode() {
    int readfd;

    if (m_method == OTHER) {
        m_statusCode = 405;
        return;
    }

    if (m_uri == "/") {
        m_returi = "/index.html";
    } else {
        m_returi = m_uri;
    }
    m_returi = "../resource/webserver/html" + m_returi;

    if ( (readfd = open(m_returi.c_str(), O_RDONLY)) == -1) {
        m_statusCode = 404;
    } else {
        m_statusCode = 200;
        m_readfd = readfd;
    }
}

void HttpBase::responseHeader() {
    std::vector<std::string> headerArray;
    std::string headerStr;

    headerArray.emplace_back(m_httpver);
    headerArray.push_back(std::to_string(m_statusCode));
    headerArray.push_back(httpStatusCodeMap[m_statusCode]);
    headerStr = StrUtil::implode(headerArray, " ");
    headerStr += "\r\n";
    headerStr += "Server: NetworkServer\r\n\r\n";
    addResponse(m_connfd, headerStr.c_str());
}

void HttpBase::responseBody() {
    size_t len = 0;
    char buf[1024];

    if (m_statusCode == 200) {
        while ( (len = (size_t) read(m_readfd, buf, 1024)) > 0) {
            if (addResponse(m_connfd, buf)) {
                break;
            }
        }
        close(m_readfd);
    }

}

size_t HttpBase::addResponse(int fd, const char *message) {
    size_t len;
    len = strlen(message);
    if (write(fd, message, len) != len) {
        std::cerr << "Error: Writing a response" << std::endl;
    }
    return len;
}

void HttpBase::process() {
    request();
    setStatusCode();
    responseHeader();
    responseBody();
}

void HttpBase::outputAccessLog(std::ofstream &accessLog) {
    std::vector<std::string> logElementArray;
    logElementArray.push_back(std::to_string(getpid()));
    logElementArray.push_back(m_remoteIp + std::string(":") + std::to_string(m_remotePort));
    logElementArray.push_back(TimeUtil::getNow());
    logElementArray.push_back(m_httpver);
    logElementArray.push_back(m_methodStr);
    logElementArray.push_back(m_uri);
    logElementArray.push_back(std::to_string(m_statusCode));

    std::string accessLogStr = StrUtil::implode(logElementArray, " ");
    accessLog << accessLogStr << std::endl;
}

