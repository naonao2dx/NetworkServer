//
// Created by 竹内 直 on 2018/03/02.
//

#ifndef WEBSERVER_SIGNAL_H
#define WEBSERVER_SIGNAL_H

#include <csignal>

typedef void Sigfunc(int);

class Signal {

public:
    static Sigfunc * Handle(int signo, Sigfunc *func);


private:
    static Sigfunc * handle(int signo, Sigfunc *func);


};

#endif //WEBSERVER_SIGNAL_H
