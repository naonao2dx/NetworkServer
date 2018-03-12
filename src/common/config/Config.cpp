//
// Created by 竹内 直 on 2018/03/09.
//

#include <fstream>
#include <iostream>
#include <map>
#include "Config.h"
#include "../code/StrUtil.h"

Config::Config() {
    std::string buf;
    std::string key;
    std::string value;

    std::ifstream ifs(m_configFilePath);
    if (!ifs) {
        std::cerr << "Could not open the file: " << m_configFilePath << std::endl;
        std::exit(1);
    }

    // Read config file every line
    while (getline(ifs, buf)) {
        // Split key and value
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

int Config::getListeningPort() const {
    return m_ListeningPort;
}

int Config::getStartServer() const {
    return m_startServer;
}

std::string &Config::getAccesslogFilePath() {
    return m_accesslogFilePath;
}