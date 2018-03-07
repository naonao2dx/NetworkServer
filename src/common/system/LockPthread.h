//
// Created by Nao on 2018/03/05.
//

#ifndef WEBSERVER_LOCKPTHREAD_H
#define WEBSERVER_LOCKPTHREAD_H

#include <pthread.h>
#include "Lock.h"
#include "../code/Singleton.h"

class LockPthread : public Singleton<LockPthread>, public Lock{
private:
    friend class Singleton<LockPthread>;
    LockPthread(){};

public:
    void init() override;
    void wait() override;
    void release() override;

    pthread_mutex_t *mptr;
};


#endif //WEBSERVER_LOCKPTHREAD_H
