cmake_minimum_required(VERSION 3.9)
project(NetworkServer)

set(CMAKE_CXX_STANDARD 11)

add_executable(NetworkServer src/main.cpp src/common/system/PIDFile.h src/common/system/Signal.h src/common/system/Signal.cpp src/common/system/Signal.h src/server/manager/ServerManager.cpp src/server/manager/ServerManager.h src/server/web/WebServer.cpp src/server/web/WebServer.h src/server/protocol/tcp/TCP.cpp src/server/protocol/tcp/TCP.h src/common/system/LockFcntl.cpp src/common/system/LockFcntl.h src/server/AbstractServer.h src/common/system/Daemon.cpp src/common/system/Daemon.h src/common/code/Singleton.h src/common/system/Lock.h src/common/system/LockPthread.cpp src/common/system/LockPthread.h src/common/code/StrUtil.cpp src/common/code/StrUtil.h src/common/code/TimeUtil.cpp src/common/code/TimeUtil.h src/server/protocol/http/HttpController.cpp src/server/protocol/http/HttpController.h src/server/config/Config.cpp src/server/config/Config.h src/server/protocol/http/HttpRequest.h src/server/protocol/http/HttpResponse.h src/server/protocol/http/APIController.cpp src/server/protocol/http/APIController.h)

target_link_libraries(NetworkServer pthread)