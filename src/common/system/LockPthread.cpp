//
// Created by Nao on 2018/03/05.
//

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "LockPthread.h"

void LockPthread::init() {
    int fd;
    pthread_mutexattr_t mattr;

    fd = open("/dev/zero", O_RDWR, 0);
    mptr = (pthread_mutex_t*) mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    pthread_mutexattr_init(&mattr);
    pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(mptr, &mattr);
}

void LockPthread::wait() {
    pthread_mutex_lock(mptr);
}

void LockPthread::release() {
    pthread_mutex_unlock(mptr);
}