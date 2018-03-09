//
// Created by 竹内 直 on 2018/03/09.
//

#include <fstream>
#include <iostream>
#include <map>
#include "ConfigWebServer.h"
#include "../../common/code/StrUtil.h"

ConfigWebServer::ConfigWebServer() {
    std::string buf;
    std::string key;
    std::string value;

    std::ifstream ifs(m_configFilePath);
    if (!ifs) {
        std::cerr << "Could not open the file: " << m_configFilePath << std::endl;
        std::exit(1);
    }

    while (getline(ifs, buf)) {
        std::vector<std::string> configRow;
        StrUtil::split(buf, "=", configRow);

        key = StrUtil::trim(configRow[0]);
        value = StrUtil::trim(configRow[1]);

        if (key == "ListeningPort") {
            m_ListeningPort = std::stoi(value);
        } else if (key == "StartServer") {
            m_startServer = std::stoi(value);
        } else if (key == "AccessLogFilePath") {
            m_accesslogFilePath = StrUtil::trim(value, "\"");
        }

    }
}

int ConfigWebServer::getListeningPort() const {
    return m_ListeningPort;
}

int ConfigWebServer::getStartServer() const {
    return m_startServer;
}

std::string &ConfigWebServer::getAccesslogFilePath() {
    return m_accesslogFilePath;
}