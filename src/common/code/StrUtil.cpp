//
// Created by 竹内 直 on 2018/03/06.
//

#include "StrUtil.h"
std::string StrUtil::implode(std::vector<std::string> strArray, std::string delimiter) {
    std::string retStr;
    for(const auto& str : strArray) {
        retStr += str;
        retStr += delimiter;
    }
    retStr.pop_back();
    return retStr;
}

std::string StrUtil::trim(const std::string &string, const char *trimCharList) {
    std::string retStr;

    std::string::size_type left = string.find_first_not_of(trimCharList);
    if(left != std::string::npos) {
        std::string::size_type right = string.find_last_not_of(trimCharList);
        retStr = string.substr(left, right - left + 1);
    }

    return retStr;
}