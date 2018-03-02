#include <iostream>
#include <unistd.h>
#include "common/PIDFile.h"
#include "common/system/Signal.h"
#include "server/ServerManager.h"

#define MAXFD 64

void daemonInitialize() {
    int i = 0;
    pid_t pid = 0;

    std::cout << getpid() << std::endl;
    // 親プロセスを終了
    if ( (pid = fork()) != 0 )
        exit(0);
    // セッションリーダー化
    setsid();
    // HUPシグナルを無視
    Signal::Handle(SIGHUP, SIG_IGN);
    // 親プロセスを切り離し
    if ( (pid = fork()) != 0)
        exit(0);

    // ファイルモード作成マスクのクリア
    umask(0);
    // 全てのファイルディスクリプタをクローズ
    for (i = 0; i < MAXFD; i++) {
        close(i);
    }

}

int main(int argc, char** argv) {
    if (1 == argc) {
        std::cerr << "execute [options]" << std::endl;
        std::cerr << "[options]" << std::endl;
        std::cerr << "    start: start by background." << std::endl;
        std::cerr << "     stop: stop server application" << std::endl;
    }

    #define CMD_START__  (0x0001)
    #define CMD_STOP__  (0x0002)
    #define CMD_CONSOLE__ (0x0004)

    //#define SERVER_APPLICATION_NAME "WebServer"
    std::string strExec(argv[0]);

    u_int8_t argFlag = 0;

    while (--argc > 0 && **++argv) {
        if (0 == strncmp(*argv, "start", 5)) {
            argFlag = CMD_START__;
        } else if (0 == strncmp(*argv, "stop", 4)) {
            argFlag = CMD_STOP__;
        } else if (0 == strncmp(*argv, "console", 7)) {
            argFlag = CMD_CONSOLE__;
        }
    }

    switch (argFlag) {
        case CMD_START__: {
            // pidファイルで多重起動チェック
            if (PIDFile::isExistPIDFile(strExec)) {
                std::cerr << strExec << " process is already exist !" << std::endl;
                std::cerr << "Check your pid file !" << std::endl;
                std::cerr << "Running process id is " << PIDFile::getExistPID(strExec);
                exit(1);
            }
            // デーモンプロセス化
            daemonInitialize();

            // PIDファイルの作成
            PIDFile::makePIDFile(strExec, getpid());
            break;
        }
        case CMD_STOP__: {
            // システムコマンドでプロセス終了
            std::string strCommand = "kill -TERM " + PIDFile::getExistPID(strExec);
            int ret = system(strCommand.c_str());
            if (ret == 0) {
                // PIDファイルの削除
                PIDFile::removePIDFile(strExec);
            } else {
                std::cerr << "Failed to stop process: " << PIDFile::getExistPID(strExec) << std::endl;
            }
            return (0);
        }
        case CMD_CONSOLE__: {
            // pidファイルで多重起動チェック
            if (PIDFile::isExistPIDFile(strExec)) {
                std::cerr << strExec << " process is already exist !" << std::endl;
                std::cerr << "Check your pid file !" << std::endl;
                std::cerr << "Running process id is " << PIDFile::getExistPID(strExec);
                exit(1);
            }
            break;
        }
    }
    ServerManager *svManager = ServerManager::getInstance();
    svManager->constructServer();
    return 0;
}