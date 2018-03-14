//
// Created by 竹内 直 on 2018/03/12.
//

#ifndef NETWORKSERVER_HTTPRESPONSE_H
#define NETWORKSERVER_HTTPRESPONSE_H


#include <string>
#include <unordered_map>

class HttpResponse {
private:
    std::unordered_map<std::string, std::string> m_responseHeader;
    std::string m_responseBody;
    std::string m_uri;
    int m_statusCode;

public:
    inline int getStatusCode() const {
        return m_statusCode;
    }

    inline void setStatusCode(int statusCode) {
        m_statusCode = statusCode;
    }

    inline std::string getUri() const {
        return m_uri;
    }

    inline void setUri(std::string uri) {
        m_uri = uri;
    }

    inline std::unordered_map<std::string, std::string> getResponseHeader() const {
        return m_responseHeader;
    }

    inline void setResponseHeader(std::unordered_map<std::string, std::string> &responseHeader) {
        m_responseHeader = responseHeader;
    }
};

#endif //NETWORKSERVER_HTTPRESPONSE_H
