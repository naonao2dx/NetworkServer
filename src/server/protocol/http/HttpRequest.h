//
// Created by 竹内 直 on 2018/03/12.
//

#ifndef NETWORKSERVER_HTTPREQUEST_H
#define NETWORKSERVER_HTTPREQUEST_H


#include <string>
#include <unordered_map>
#include <iostream>

class HttpRequest {
private:
    std::string _remoteAddress;
    int _remotePort;
    std::string _ipProtocol;
    std::string _httpVersion;
    std::string _method;
    std::string _uri;
    std::unordered_map<std::string, std::string> _requestHeader;
    std::string _requestBody;

public:
    inline std::string getRemoteAddress() {
        return _remoteAddress;
    }

    inline void setRemoteAddress(char* remoteAddress) {
        _remoteAddress = std::string(remoteAddress);
    }

    inline int getRemotePort() const {
        return _remotePort;
    }

    inline void setRemotePort(int port) {
        _remotePort = port;
    }

    inline std::string getIpProtocol() const {
        return _ipProtocol;
    }

    inline void setIpProtocol(std::string ipProtocol) {
        _ipProtocol = ipProtocol;
    }

    inline std::string getHttpVersion() const {
        return _httpVersion;
    }

    inline void setHttpVersion(char* httpver) {
        _httpVersion = std::string(httpver);
    }

    inline std::string getMethod() const {
        return _method;
    }

    inline void setMethod(char* method) {
        _method = std::string(method);
    }

    inline std::string getUri() const {
        return _uri;
    }

    inline void setUri(char* uri) {
        _uri = std::string(uri);
    }

    inline std::unordered_map<std::string, std::string> getRequestHeader() const {
        return _requestHeader;
    }

    inline void setRequestHeader(std::unordered_map<std::string, std::string> &requestHeader) {
        _requestHeader = requestHeader;
    }
};


#endif //NETWORKSERVER_HTTPREQUEST_H
