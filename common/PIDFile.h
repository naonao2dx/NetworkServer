//
// Created by 竹内 直 on 2018/02/22.
//

#ifndef WEBSERVER_PIDFILE_H
#define WEBSERVER_PIDFILE_H

#include <string>
#include <sys/stat.h>
#include <fstream>
#include <sstream>

class PIDFile
{
public:
    PIDFile(std::string processName) {

    }

    virtual ~PIDFile() {

    }

    static bool isExistPIDFile(std::string execName) {
        std::string filePath(execName + ".pid");
        return (isExist(filePath));
    }

    static std::string getExistPID(std::string strProcessName) {
        std::ifstream fin(strProcessName + ".pid");
        if (!fin) {
            // エラー処理
        }
        std::stringstream strstream;
        strstream << fin.rdbuf();
        fin.close();

        return strstream.str();
    }

    static void makePIDFile(std::string strExec, pid_t pid) {
        std::ofstream fout(strExec + ".pid");
        fout << pid;
        fout.close();
    }

    static void removePIDFile(std::string strExec) {
        std::string filePath(strExec + ".pid");
        if (remove(filePath.c_str()) == 0) {
            std::cout << "Removed the pid file \"" << filePath << "\"" << std::endl;
        } else {
            std::cout << "Failed to remove the pid file \"" << filePath << "\"" << std::endl;
            exit(1);
        }
    }

private:
    static bool isExist(std::string filePath) {
        struct stat stattat;
        int ret = stat(filePath.c_str(), &stattat);
        if (0 != ret) {
            return false;
        }
        return true;
    }




};

#endif //WEBSERVER_PIDFILE_H

