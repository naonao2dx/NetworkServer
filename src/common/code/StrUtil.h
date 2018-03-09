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
    template <typename List>
    static void split(const std::string& s, const std::string& delim, List& result) {
        result.clear();

        using string = std::string;
        string::size_type pos = 0;

        while (pos != string::npos ) {
            string::size_type p = s.find(delim, pos);

            if (p == string::npos) {
                result.push_back(s.substr(pos));
                break;
            } else {
                result.push_back(s.substr(pos, p - pos));
            }

            pos = p + delim.size();
        }
    }
};


#endif //WEBSERVER_UTIL_H
