cmake_minimum_required(VERSION 3.9)
project(WebServer)

set(CMAKE_CXX_STANDARD 11)

add_executable(WebServer main.cpp common/system/PIDFile.h common/system/Signal.h common/system/Signal.cpp common/system/Signal.h server/ServerManager.cpp server/ServerManager.h server/GameServer.cpp server/GameServer.h common/protocol/TCP.cpp common/protocol/TCP.h common/system/LockFcntl.cpp common/system/LockFcntl.h common/protocol/Http.cpp common/protocol/Http.h server/AbstractServer.cpp server/AbstractServer.h common/system/Daemon.cpp common/system/Daemon.h common/code/Singleton.h)