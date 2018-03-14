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
    std::string m_remoteAddress;
    int m_remotePort;
    std::string m_ipProtocol;
    std::string m_httpVersion;
    std::string m_method;
    std::string m_uri;
    std::unordered_map<std::string, std::string> m_requestHeader;
    std::string m_requestBody;

public:
    inline std::string getRemoteAddress() {
        return m_remoteAddress;
    }

    inline void setRemoteAddress(std::string remoteAddress) {
        m_remoteAddress = std::string(remoteAddress);
    }

    inline int getRemotePort() const {
        return m_remotePort;
    }

    inline void setRemotePort(int port) {
        m_remotePort = port;
    }

    inline std::string getIpProtocol() const {
        return m_ipProtocol;
    }

    inline void setIpProtocol(std::string ipProtocol) {
        m_ipProtocol = std::string(ipProtocol);
    }

    inline std::string getHttpVersion() const {
        return m_httpVersion;
    }

    inline void setHttpVersion(std::string httpver) {
        m_httpVersion = std::string(httpver);
    }

    inline std::string getMethod() const {
        return m_method;
    }

    inline void setMethod(std::string method) {
        m_method = std::string(method);
    }

    inline std::string getUri() const {
        return m_uri;
    }

    inline void setUri(std::string uri) {
        m_uri = std::string(uri);
    }

    inline std::unordered_map<std::string, std::string> getRequestHeader() const {
        return m_requestHeader;
    }

    inline void setRequestHeader(std::unordered_map<std::string, std::string> &requestHeader) {
        m_requestHeader = requestHeader;
    }
};


#endif //NETWORKSERVER_HTTPREQUEST_H
