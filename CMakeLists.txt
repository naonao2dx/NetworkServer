cmake_minimum_required(VERSION 3.9)
project(WebServer)

set(CMAKE_CXX_STANDARD 11)

add_executable(WebServer src/main.cpp src/common/system/PIDFile.h src/common/system/Signal.h src/common/system/Signal.cpp src/common/system/Signal.h src/server/ServerManager.cpp src/server/ServerManager.h src/server/GameServer.cpp src/server/GameServer.h src/common/protocol/TCP.cpp src/common/protocol/TCP.h src/common/system/LockFcntl.cpp src/common/system/LockFcntl.h src/common/protocol/Http.cpp src/common/protocol/Http.h src/server/AbstractServer.cpp src/server/AbstractServer.h src/common/system/Daemon.cpp src/common/system/Daemon.h src/common/code/Singleton.h)