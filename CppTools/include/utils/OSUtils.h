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

        /// @brief Check if a file exists.
        /// @param fileName The name of the file to check.
        /// @return True if the file exists, false otherwise.
        static bool fileExists(const char* fileName);

        static bool deleteFileIfExists(const char* filename);

        /// @brief 
        /// @param fileName 
        /// @param content 
        /// @return 
        static bool appendToFile(std::string fileName, std::string content);

        /// @brief This function getFileName takes a full path as input and returns the file name 
        /// according to your specifications. It works by finding the last slash or backslash in 
        /// the path to extract the file name. If removeExtension is true, it also removes the file 
        /// extension by finding the last dot in the file name.
        /// @param fullPath 
        /// @param removeExtension 
        /// @return 
        static std::string getFileName(const char *fullPath, bool removeExtension);

    private:

};


#endif // __OS_UTILS_H__