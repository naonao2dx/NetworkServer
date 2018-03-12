//
// Created by 竹内 直 on 2018/03/09.
//

#include <fstream>
#include <iostream>
#include <map>
#include "Config.h"
#include "../../common/code/StrUtil.h"

Config::Config() {
    std::string buf;
    std::string key;
    std::string value;
    std::unordered_map<std::string, std::string> configMap;


    std::ifstream ifs(m_configFilePath);
    if (!ifs) {
        std::cerr << "Could not open the file: " << m_configFilePath << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Read config file every line
    while (getline(ifs, buf)) {
        // Split key and value
        std::vector<std::string> configRow;
        StrUtil::split(buf, "=", configRow);

        key = StrUtil::trim(configRow[0]);
        value = StrUtil::trim(configRow[1]);
        configMap.emplace(key, StrUtil::trim(value, "\""));
    }
    m_configMap = configMap;
}

std::string Config::getConfigValue(std::string strExec, std::string key) {
    return m_configMap.at(strExec + "." + key);
}
