//
// Created by 竹内 直 on 2018/03/06.
//

#include "StrUtil.h"
std::string StrUtil::implode(std::vector<std::string> strArray, std::string delimiter) {
    std::string str;
    for(auto itr = strArray.begin(); itr != strArray.end(); ++itr) {
        str.append(*itr);
        str.append(delimiter);
    }
    str.pop_back();
    return str;
}