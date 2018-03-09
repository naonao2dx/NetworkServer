//
// Created by 竹内 直 on 2018/03/09.
//

#ifndef NETWORKSERVER_CONFIGWEBSERVER_H
#define NETWORKSERVER_CONFIGWEBSERVER_H


#include <string>
#include "../../common/code/Singleton.h"

class ConfigWebServer : public Singleton<ConfigWebServer> {
private:
    friend class Singleton<ConfigWebServer>;
    ConfigWebServer();

public:
    int getListeningPort() const;
    int getStartServer() const;
    std::string &getAccesslogFilePath();

private:
    const std::string m_configFilePath = "../resource/webserver/config/webserver.conf";
    std::string m_accesslogFilePath = "../resource/webserver/log/access.log";
    int m_ListeningPort = 8080;
    int m_startServer = 10;
};

#endif //NETWORKSERVER_CONFIGWEBSERVER_H
