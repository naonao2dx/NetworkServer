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
};


#endif //WEBSERVER_UTIL_H
