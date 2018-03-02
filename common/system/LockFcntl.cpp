//
// Created by 竹内 直 on 2018/03/02.
//

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "LockFcntl.h"

LockFcntl* LockFcntl::s_pInstance = nullptr;

LockFcntl* LockFcntl::getInstance() {
    if (nullptr == s_pInstance) {
        try {
            s_pInstance = new LockFcntl();
        } catch (std::bad_alloc& r) {
            std::cerr << r.what() << std::endl;
        }
    }
    return s_pInstance;
}

void LockFcntl::init(std::string filepath) {
    char* lockfile = new char[filepath.size() + 1];
    std::strcpy(lockfile, filepath.c_str());
    mktemp(lockfile);
    lockfd = open(lockfile, O_CREAT | O_WRONLY, FILESEC_MODE);
    unlink(lockfile);

    lockIt.l_type = F_WRLCK;
    lockIt.l_whence = SEEK_SET;
    lockIt.l_start = 0;
    lockIt.l_len = 0;

    unlockIt.l_type = F_WRLCK;
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