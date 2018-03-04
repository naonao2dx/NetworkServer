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
