#ifndef __OS_UTILS_H__
#define __OS_UTILS_H__ 1

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdio>    // For remove()
#include <fstream>   // For ifstream


class OSUtils
{
    public:

        static bool fileExists(const char* fileName);

        static bool deleteFileIfExists(const char* filename);

    private:

};


#endif // __OS_UTILS_H__