//
// Created by Nao on 2018/03/04.
//

#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include "Daemon.h"
#include "Signal.h"

#define MAXFD 64

void Daemon::init() {
    pid_t pid = 0;

    std::cout << getpid() << std::endl;
    // kill parent process
    if ( (pid = fork()) != 0 )
        exit(0);
    // set session leader
    setsid();
    // ignore HUP signal
    Signal::Handle(SIGHUP, SIG_IGN);
    // kill parent process
    if ( (pid = fork()) != 0)
        exit(0);

    umask(0);
    // close all file descriptor
    for (auto i = 0; i < MAXFD; i++) {
        close(i);
    }
}
