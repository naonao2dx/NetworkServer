//
// Created by 竹内 直 on 2018/02/22.
//

#ifndef WEBSERVER_PIDFILE_H
#define WEBSERVER_PIDFILE_H

#include <string>
#include <sys/stat.h>

class PIDFile
{
public:
    PIDFile(std::string processName) {

    }

    virtual ~PIDFile() {

    }

    static bool isExistPIDFile(std::string processName) {
        std::string filePath = processName + ".pid";
        return (isExist(filePath));
    }

protected:
    static bool isExist(std::string filePath) {
        struct stat stat;
        int ret = stat(filePath.c_str(), &stat);
        if (0 != ret) {
            return false;
        }
        return true;
    }


};

#endif //WEBSERVER_PIDFILE_H

