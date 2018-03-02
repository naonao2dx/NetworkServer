cmake_minimum_required(VERSION 3.9)
project(WebServer)

set(CMAKE_CXX_STANDARD 11)

add_executable(WebServer main.cpp common/PIDFile.h common/system/Signal.h common/system/Signal.cpp common/system/Signal.h server/ServerManager.cpp server/ServerManager.h server/GameServer.cpp server/GameServer.h common/system/TCP.cpp common/system/TCP.h)