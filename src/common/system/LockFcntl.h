//
// Created by 竹内 直 on 2018/03/02.
//

#ifndef WEBSERVER_LOCKFCNTL_H
#define WEBSERVER_LOCKFCNTL_H

#include <string>
#include <fcntl.h>
#include "Lock.h"
#include "../code/Singleton.h"

class LockFcntl : public Singleton<LockFcntl>, public Lock {
private:
    friend class Singleton<LockFcntl>;
    LockFcntl(){};
public:
    struct flock lockIt, unlockIt;
    int lockfd = -1;

    void init() override;
    void wait() override;
    void release() override;
};

#endif //WEBSERVER_LOCKFCNTL_H
