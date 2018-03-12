//
// Created by 竹内 直 on 2018/03/08.
//

#include "HttpController.h"
#include "../../../common/code/StrUtil.h"
#include "../../../common/code/TimeUtil.h"
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <strstream>

HttpController::HttpController(int connfd, struct sockaddr* cliaddr) :
m_connfd(connfd)
{
    char ipv6addr[INET6_ADDRSTRLEN];
    char ipv4addr[INET_ADDRSTRLEN];

    struct sockaddr_in* addrv4;
    struct sockaddr_in6* addrv6;

    m_httpRequest = HttpRequest(HttpRequest());
    m_httpResponse = HttpResponse(HttpResponse());

    // Get IPv4 client socket information, and if the connection is IPv6, get IPv6 socket information.
    addrv4 = reinterpret_cast<struct sockaddr_in *>(cliaddr);
    if (strcmp(inet_ntop(AF_INET, &addrv4->sin_addr, ipv4addr, sizeof(ipv4addr)), "0.0.0.0") != 0) {
        m_httpRequest.setRemoteAddress(ipv4addr);
        m_httpRequest.setRemotePort(addrv4->sin_port);
        m_httpRequest.setIpProtocol("IPv4");
    } else {
        addrv6 = reinterpret_cast<struct sockaddr_in6 *>(cliaddr);
        inet_ntop(AF_INET6, &addrv6->sin6_addr, ipv6addr, sizeof(ipv6addr));
        m_httpRequest.setRemoteAddress(ipv6addr);
        m_httpRequest.setRemotePort(addrv6->sin6_port);
        m_httpRequest.setIpProtocol("IPv6");
    }
}

void HttpController::request() {
    char buf[1024];
    char method[10];
    char uri[100];
    char httpver[10];
    char* headerRow;
    std::vector<char* > headerArray;
    std::unordered_map<std::string, std::string> headerMap;
    std::string key;
    std::string value;

    // TODO: Reading and analyzing about over 1024 byte header
    // TODO: Reading request body

    if (read(m_connfd, buf, 1024) <= 0) {
        exit(1);
    }

    // Get request line
    std::string requestLine = strtok(buf, "\r\n");

    // Get header line
    while ((headerRow = strtok(nullptr, "\r\n"))) {
        headerArray.emplace_back(headerRow);
    }

    // Remove non-headder element
    headerArray.pop_back();

    // Make header element map
    for (auto row : headerArray) {
        key = strtok(row, ":");
        value = strtok(nullptr, ":");
        headerMap.emplace(key, StrUtil::trim(value));
    }

    m_httpRequest.setRequestHeader(headerMap);

    sscanf(requestLine.data(), "%s %s %s", method, uri, httpver);
    m_httpRequest.setMethod(method);
    m_httpRequest.setUri(uri);
    m_httpRequest.setHttpVersion(httpver);
}

void HttpController::setStatusCode() {
    int readfd;

    // Non-acceptable method
    if (m_enableMethodSet.count(m_httpRequest.getMethod()) == 0) {
        m_httpResponse.setStatusCode(405);
        return;
    }

    // Make response uri from request uri
    if (m_httpRequest.getUri() == "/") {
        m_httpResponse.setUri("/index.html");
    } else {
        m_httpResponse.setUri(m_httpRequest.getUri());
    }
    m_httpResponse.setUri("../resource/html" + m_httpResponse.getUri());

    // Set status code and return file descriptor
    if ( (readfd = open(m_httpResponse.getUri().c_str(), O_RDONLY)) == -1) {
        m_httpResponse.setStatusCode(404);
    } else {
        m_httpResponse.setStatusCode(200);
        m_readfd = readfd;
    }
}

void HttpController::responseHeader() {
    std::vector<std::string> headerArray;
    std::string headerStr;

    headerArray.emplace_back(m_httpRequest.getHttpVersion());
    headerArray.push_back(std::to_string(m_httpResponse.getStatusCode()));
    headerArray.push_back(httpStatusCodeMap[m_httpResponse.getStatusCode()]);
    headerStr = StrUtil::implode(headerArray, " ");
    headerStr += "\r\n";
    //headerStr += "Content-Type: text/html; charset=UTF-8\r\n";
    headerStr += "Date: " + TimeUtil::getNow() + "\r\n\r\n";
    addResponse(m_connfd, headerStr.c_str());
}

void HttpController::responseBody() {
    size_t len = 0;
    char buf[1024];

    if (m_httpResponse.getStatusCode() == 200) {
        while ( (len = (size_t) read(m_readfd, buf, 1024)) > 0) {
            if (addResponse(m_connfd, buf, len)) {
                break;
            }
        }
        close(m_readfd);
    }

}

size_t HttpController::addResponse(int fd, const char *message, size_t len) {
    if (len == 0) {
        len = strlen(message);
    }

    if (write(fd, message, len) != len) {
        std::cerr << "Error: Writing a response" << std::endl;
    }
    return len;
}

void HttpController::process() {
    request();
    setStatusCode();
    responseHeader();
    responseBody();
}

void HttpController::outputAccessLog(std::ofstream &accessLog) {
    std::vector<std::string> logElementArray;
    std::unordered_map<std::string, std::string> requestHeader = m_httpRequest.getRequestHeader();

    logElementArray.emplace_back(std::to_string(getpid()));
    logElementArray.emplace_back(m_httpRequest.getRemoteAddress() + std::string(":") + std::to_string(m_httpRequest.getRemotePort()));
    logElementArray.emplace_back(std::string("(" + m_httpRequest.getIpProtocol() + ")"));
    logElementArray.emplace_back("[" + TimeUtil::getNow() + "]");
    logElementArray.emplace_back(m_httpRequest.getHttpVersion());
    logElementArray.emplace_back(m_httpRequest.getMethod());
    logElementArray.emplace_back(m_httpRequest.getUri());
    logElementArray.emplace_back(std::to_string(m_httpResponse.getStatusCode()));
    logElementArray.emplace_back(requestHeader.at("User-Agent"));

    std::string accessLogStr = StrUtil::implode(logElementArray, " ");
    accessLog << accessLogStr << std::endl;
}

