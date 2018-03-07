//
// Created by 竹内 直 on 2018/03/07.
//
#include <sstream>
#include "TimeUtil.h"

std::string TimeUtil::getNow() {
    char buf[100];
    std::stringstream s;
    time_t now = std::time(nullptr);
    std::tm* lt = std::localtime(&now);
    sprintf(buf,"%4d-%02d-%02d %02d:%02d:%02d", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    return std::string(buf);
}