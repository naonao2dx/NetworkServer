//
// Created by 竹内 直 on 2018/03/02.
//

#include <iostream>
#include "Signal.h"

Sigfunc* Signal::handle(int signo, Sigfunc *func) {
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    } else {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;
#endif
    }
    if (sigaction(signo, &act, &oact) < 0)
        return(SIG_ERR);
    return(oact.sa_handler);
}

Sigfunc * Signal::Handle(int signo, Sigfunc *func) {
    Sigfunc *sigfunc;
    if ( (sigfunc = Signal::handle(signo, func)) == SIG_ERR)
        std::cerr << "signal error" << std::endl;
    return(sigfunc);
}
