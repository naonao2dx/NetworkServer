#include <iostream>
#include <unistd.h>
#include "common/PIDFile.h"

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
    signal(SIGHUP, SIG_IGN);
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
        std::cout << "execute [options]" << std::endl;
        std::cout << "[options]" << std::endl;
        std::cout << "    start: start by background." << std::endl;
        std::cout << "     stop: stop server application" << std::endl;
    }

    #define CMD_START__  (0x0001)
    #define CMD_STOP__  (0x0002)

    //#define SERVER_APPLICATION_NAME "WebServer"
    std::string strExec(argv[0]);

    u_int8_t argFlag = 0;

    while (--argc > 0 && **++argv) {
        if (0 == strncmp(*argv, "start", 5)) {
            argFlag = CMD_START__;
        } else if (0 == strncmp(*argv, "stop", 4)) {
            argFlag = CMD_STOP__;
        }
    }

    switch (argFlag) {
        case CMD_START__: {
            // pidファイルで多重起動チェック
            if (PIDFile::isExistPIDFile(strExec)) {
                std::cout << strExec << " process is already exist !" << std::endl;
                std::cout << "Check your pid file !" << std::endl;
                std::cout << "Running process id is " << PIDFile::getExistPID(strExec);
                exit(1);
            }
            // デーモンプロセス化
            daemonInitialize();

            // PIDファイルの作成
            PIDFile::makePIDFile(strExec, getpid());
            for(;;)
                pause();
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
                std::cout << "Failed to stop process: " << PIDFile::getExistPID(strExec) << std::endl;
            }
            break;
        }
    }
    return 0;
}