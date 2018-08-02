//
// Created by 竹内 直 on 2018/03/09.
//

#ifndef NETWORKSERVER_CONFIGWEBSERVER_H
#define NETWORKSERVER_CONFIGWEBSERVER_H


#include <string>
#include <unordered_map>
#include "../../common/code/Singleton.h"

class Config : public Singleton<Config> {
private:
    friend class Singleton<Config>;

    Config();

public:
    std::string getConfigValue(std::string strExec, std::string key);

private:
    std::unordered_map<std::string, std::string> _configMap;
    const std::string _configFilePath = "../resource/config/NetworkServer.conf";
};

#endif //NETWORKSERVER_CONFIGWEBSERVER_H
