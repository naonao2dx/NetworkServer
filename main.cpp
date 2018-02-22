#include <iostream>

int main(int argc, char** argv) {
    if (1 == argc) {
        printf("\n");
        printf("execute [options] \n");
        printf("[options]\n");
        printf("    start: start by background. \n");
        printf("     stop: stop server application");
        printf("\n");
    }

    #define ARG_START__  (0x0001)
    #define ARG_STOP__  (0x0002)

    #define SERVER_APPLICATION_NAME "WebServer"

    u_int8_t argFlag = 0;

    while (--argc > 0 && **++argv) {
        if (0 == strncmp(*argv, "start", 5)) {
            argFlag = ARG_START__;
        } else if (0 == strncmp(*argv, "stop", 4)) {
            argFlag = ARG_STOP__;
        }
    }

    switch (argFlag) {
        case ARG_START__:
            break;
        case ARG_STOP__:
            break;
    }
    return 0;
}