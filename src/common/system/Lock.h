//
// Created by Nao on 2018/03/05.
//

#ifndef WEBSERVER_LOCK_H
#define WEBSERVER_LOCK_H

class Lock {

public:
    virtual void init() = 0;
    virtual void wait() = 0;
    virtual void release() = 0;

};


#endif //WEBSERVER_LOCK_H
