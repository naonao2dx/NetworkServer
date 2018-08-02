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
#include <sstream>
#include <cstring>
#include <new>


HttpController::HttpController(int connfd, struct sockaddr* cliaddr) :
_connfd(connfd)
{
    char ipv6addr[INET6_ADDRSTRLEN];
    char ipv4addr[INET_ADDRSTRLEN];

    struct sockaddr_in* addrv4;
    struct sockaddr_in6* addrv6;

    _httpRequest = HttpRequest(HttpRequest());
    _httpResponse = HttpResponse(HttpResponse());

    // Get IPv4 client socket information, and if the connection is IPv6, get IPv6 socket information.
    addrv4 = reinterpret_cast<struct sockaddr_in *>(cliaddr);
    if (strcmp(inet_ntop(AF_INET, &addrv4->sin_addr, ipv4addr, sizeof(ipv4addr)), "0.0.0.0") != 0) {
        _httpRequest.setRemoteAddress(ipv4addr);
        _httpRequest.setRemotePort(addrv4->sin_port);
        _httpRequest.setIpProtocol("IPv4");
    } else {
        addrv6 = reinterpret_cast<struct sockaddr_in6 *>(cliaddr);
        inet_ntop(AF_INET6, &addrv6->sin6_addr, ipv6addr, sizeof(ipv6addr));
        _httpRequest.setRemoteAddress(ipv6addr);
        _httpRequest.setRemotePort(addrv6->sin6_port);
        _httpRequest.setIpProtocol("IPv6");
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

    if (read(_connfd, buf, 1024) <= 0) {
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

    _httpRequest.setRequestHeader(headerMap);

    sscanf(requestLine.data(), "%s %s %s", method, uri, httpver);
    _httpRequest.setMethod(method);
    _httpRequest.setUri(uri);
    _httpRequest.setHttpVersion(httpver);
}

void HttpController::setStatusCode() {
    // Non-acceptable method
    if (_enableMethodSet.count(_httpRequest.getMethod()) == 0) {
        _httpResponse.setStatusCode(405);
        return;
    }

    // Make response uri from request uri
    if (_httpRequest.getUri() == "/") {
        _httpResponse.setUri("/index.html");
    } else {
        _httpResponse.setUri(_httpRequest.getUri());
    }
    _httpResponse.setUri("../resource/html" + _httpResponse.getUri());

    _ifs.open(_httpResponse.getUri(), std::ios::in | std::ios::binary);
    if (!_ifs) {
        _httpResponse.setStatusCode(404);
    } else {
        _httpResponse.setStatusCode(200);
    }
}

void HttpController::responseHeader() {
    std::vector<std::string> headerArray;
    std::string headerStr;

    headerArray.emplace_back(_httpRequest.getHttpVersion());
    headerArray.push_back(std::to_string(_httpResponse.getStatusCode()));
    headerArray.push_back(httpStatusCodeMap[_httpResponse.getStatusCode()]);
    headerStr = StrUtil::implode(headerArray, " ");
    headerStr += "\r\n";
    //headerStr += "Content-Type: text/html; charset=UTF-8\r\n";
    headerStr += "Date: " + TimeUtil::getNow() + "\r\n\r\n";
    addResponse(_connfd, headerStr.c_str());
}

void HttpController::responseBody() {
    size_t len = 0;

    if (_httpResponse.getStatusCode() == 200) {
        _ifs.seekg(0, std::ifstream::end);
        auto fileSize = static_cast<size_t>(_ifs.tellg());
        _ifs.seekg(0, std::ifstream::beg);

        auto buf = new char[fileSize];
        _ifs.read(buf, fileSize);
        addResponse(_connfd, buf, fileSize);
        delete [] buf;
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
    std::unordered_map<std::string, std::string> requestHeader = _httpRequest.getRequestHeader();

    logElementArray.emplace_back(std::to_string(getpid()));
    logElementArray.emplace_back(_httpRequest.getRemoteAddress() + std::string(":") + std::to_string(_httpRequest.getRemotePort()));
    logElementArray.emplace_back(std::string("(" + _httpRequest.getIpProtocol() + ")"));
    logElementArray.emplace_back("[" + TimeUtil::getNow() + "]");
    logElementArray.emplace_back(_httpRequest.getHttpVersion());
    logElementArray.emplace_back(_httpRequest.getMethod());
    logElementArray.emplace_back(_httpRequest.getUri());
    logElementArray.emplace_back(std::to_string(_httpResponse.getStatusCode()));
    logElementArray.emplace_back(requestHeader.at("User-Agent"));

    std::string accessLogStr = StrUtil::implode(logElementArray, " ");
    accessLog << accessLogStr << std::endl;
}

