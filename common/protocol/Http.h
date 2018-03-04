//
// Created by admin on 2018/03/04.
//

#ifndef WEBSERVER_HTTP_H
#define WEBSERVER_HTTP_H


#include <string>

class Http {
public:
    static void process(int sockfd);

private:
    static int response(int fd, std::string message);
};


#endif //WEBSERVER_HTTP_H
