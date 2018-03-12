//
// Created by Nao on 2018/03/04.
//

#ifndef WEBSERVER_ABSTRACTSERVER_H
#define WEBSERVER_ABSTRACTSERVER_H


class AbstractServer {
public:
    AbstractServer() = default;
    AbstractServer(const AbstractServer &rhs) = default;
    virtual ~AbstractServer() = default;

    virtual void start() = 0;
    virtual void killChild() = 0;

};


#endif //WEBSERVER_ABSTRACTSERVER_H
