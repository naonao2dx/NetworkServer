//
// Created by 竹内 直 on 2018/03/02.
//

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "LockFcntl.h"


void LockFcntl::init() {
    char* lockfile = const_cast<char *>("NetworkServer.lock");
    mkstemp(lockfile);
    lockfd = open(lockfile, O_CREAT | O_WRONLY, 4); //  4 = FILESEC_MODE
    unlink(lockfile);

    lockIt.l_type = F_WRLCK;
    lockIt.l_whence = SEEK_SET;
    lockIt.l_start = 0;
    lockIt.l_len = 0;

    unlockIt.l_type = F_UNLCK;
    unlockIt.l_whence = SEEK_SET;
    unlockIt.l_start = 0;
    unlockIt.l_len = 0;
}

void LockFcntl::wait() {
    int rc;
    while ( ( rc = fcntl(lockfd, F_SETLKW, &lockIt)) < 0) {
        if (errno == EINTR)
            continue;
        else
            std::cerr << "fcntl error for LockFcntl::wait" << std::endl;
    }

}

void LockFcntl::release() {
    if (fcntl(lockfd, F_SETLKW, &unlockIt) < 0)
        std::cerr << "fcntl error for LockFcntl::release" << std::endl;
}