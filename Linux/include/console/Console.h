#ifndef __CONSOLE__H__
#define __CONSOLE__H__ 1


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <thread>
#include <mutex>
#include <condition_variable>


class Console
{
    public:

        Console();

        ~Console();

        const static void printTable(std::vector<std::string> labels, std::vector<std::vector<std::string>> tableMatrix);

        // int executeCommand(const char* command, int mode, std::string& stdOut);
        // bool commandFinished(std::string& stdOut, int& retCode);

    private:
        /*
        bool finished_;
        std::string stdOut_;
        int return_code_;
        std::mutex mutex_;
        std::condition_variable finished_cv_;
        std::mutex cv_mutex_;
        **/

};


#endif // __CONSOLE__H__
