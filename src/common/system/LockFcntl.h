//
// Created by 竹内 直 on 2018/03/02.
//

#ifndef WEBSERVER_LOCKFCNTL_H
#define WEBSERVER_LOCKFCNTL_H


#include <string>
#include <fcntl.h>

class LockFcntl {
public:
    static LockFcntl* getInstance();

    struct flock lockIt, unlockIt;
    int lockfd = -1;

    void init(std::string filepath);
    void wait();
    void release();

private:
    static LockFcntl* s_pInstance;
    LockFcntl(){};
    virtual ~LockFcntl(){};
};


#endif //WEBSERVER_LOCKFCNTL_H
