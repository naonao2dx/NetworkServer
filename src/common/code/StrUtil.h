//
// Created by 竹内 直 on 2018/03/06.
//

#ifndef WEBSERVER_UTIL_H
#define WEBSERVER_UTIL_H


#include <string>
#include <vector>

class StrUtil {
public:
    static std::string implode(std::vector<std::string> strArray, std::string delimiter);
    static std::string trim(const std::string& string, const char* trimCharList = " \t\v\r\n");
    static void split(const std::string& s, const std::string& delim, std::vector<std::string>& result);
};


#endif //WEBSERVER_UTIL_H
