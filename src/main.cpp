#include <iostream>
#include <cstring>
#include <unistd.h>
#include "common/system/Signal.h"
#include "server/manager/ServerManager.h"
#include "common/system/Daemon.h"
#include "common/system/PIDFile.h"

int main(int argc, char** argv) {
    std::string strExec;

    if (3 != argc) {
        std::cerr << "execute [server] [command]" << std::endl;
        std::cerr << "[server]" << std::endl;
        std::cerr << "      Web: Web server" << std::endl;
        std::cerr << "      API: API server" << std::endl;
        std::cerr << "[command]" << std::endl;
        std::cerr << "  console: start server by foreground" << std::endl;
        std::cerr << "    start: start server by background." << std::endl;
        std::cerr << "     stop: stop server application" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    #define CMD_START__  (0x0001)
    #define CMD_STOP__  (0x0002)
    #define CMD_CONSOLE__ (0x0004)

    u_int8_t argFlag = 0;

    while (--argc > 0 && **++argv) {
        if (0 == strncmp(*argv, "Web", 3)) {
            strExec = *argv;
        } else if (0 == strncmp(*argv, "API", 3)) {
            strExec = *argv;
        } else if (0 == strncmp(*argv, "start", 5)) {
            argFlag = CMD_START__;
        } else if (0 == strncmp(*argv, "stop", 4)) {
            argFlag = CMD_STOP__;
        } else if (0 == strncmp(*argv, "console", 7)) {
            argFlag = CMD_CONSOLE__;
        }
    }

    switch (argFlag) {
        case CMD_START__: {
            // Check multiple start-up with .pid file
            if (PIDFile::isExistPIDFile(strExec)) {
                std::cerr << strExec << " process is already exist !" << std::endl;
                std::cerr << "Check your pid file !" << std::endl;
                std::cerr << "Running process id is " << PIDFile::getExistPID(strExec);
                std::exit(EXIT_FAILURE);
            }
            // Daemonize
            Daemon::init();

            // Make .pid file
            PIDFile::makePIDFile(strExec, getpid());
            break;
        }
        case CMD_STOP__: {
            // kill process
            pid_t pid = PIDFile::getExistPID(strExec);
            int ret = kill(pid, SIGTERM);
            if (ret == 0) {
                // Remove .pid file
                PIDFile::removePIDFile(strExec);
            } else {
                std::cerr << "Failed to stop process: " << PIDFile::getExistPID(strExec) << std::endl;
            }
            std::exit(EXIT_SUCCESS);
        }
        case CMD_CONSOLE__: {
            // Check multiple start-up with .pid file
            if (PIDFile::isExistPIDFile(strExec)) {
                std::cerr << strExec << " process is already exist !" << std::endl;
                std::cerr << "Check your pid file !" << std::endl;
                std::cerr << "Running process id is " << PIDFile::getExistPID(strExec);
                std::exit(EXIT_FAILURE);
            }
            break;
        }
        default: {
            std::cerr << "execute [server] [command]" << std::endl;
            std::cerr << "[server]" << std::endl;
            std::cerr << "      Web: Web server" << std::endl;
            std::cerr << "      API: API server" << std::endl;
            std::cerr << "[command]" << std::endl;
            std::cerr << "  console: start server by foreground" << std::endl;
            std::cerr << "    start: start server by background." << std::endl;
            std::cerr << "     stop: stop server application" << std::endl;
            std::exit(EXIT_FAILURE);
        }

    }
    auto serverManager = ServerManager::getInstance();
    serverManager->constructServer(strExec);
    std::exit(EXIT_SUCCESS);
}