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