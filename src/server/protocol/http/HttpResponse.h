//
// Created by 竹内 直 on 2018/03/12.
//

#ifndef NETWORKSERVER_HTTPRESPONSE_H
#define NETWORKSERVER_HTTPRESPONSE_H


#include <string>
#include <unordered_map>

class HttpResponse {
private:
    std::unordered_map<std::string, std::string> _responseHeader;
    std::string _responseBody;
    std::string _uri;
    int _statusCode;

public:
    inline int getStatusCode() const {
        return _statusCode;
    }

    inline void setStatusCode(int statusCode) {
        _statusCode = statusCode;
    }

    inline std::string getUri() const {
        return _uri;
    }

    inline void setUri(std::string uri) {
        _uri = uri;
    }

    inline std::unordered_map<std::string, std::string> getResponseHeader() const {
        return _responseHeader;
    }

    inline void setResponseHeader(std::unordered_map<std::string, std::string> &responseHeader) {
        _responseHeader = responseHeader;
    }
};

#endif //NETWORKSERVER_HTTPRESPONSE_H
