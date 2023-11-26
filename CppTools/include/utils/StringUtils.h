#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__ 1

#include <iomanip>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstring>


class StringUtils
{
    public:

        //
        // string manipulation
        //


        // deprecated
        //static std::string toLower(const char* str);

        static void toLower(std::string& str);

        static void toUpper(std::string& str);

        static std::string toLowerCopy(const char* str);

        static std::string toUpperCopy(const char* str);

        static void lTrim(std::string &s);

        static void rTrim(std::string &s);

        static void trim(std::string &s);

        static std::string ltrimCopy(const char* s);

        static std::string rtrimCopy(const char* s);

        static std::string trimCopy(const char* s);

        //
        // type to string operations
        //

        static std::string toHexString(unsigned long n);

        static std::string toHexString(unsigned int n);
        
        static std::string toHexString(unsigned short n);

        static std::string toString(std::vector<std::string> vec);
        
         static std::string toString(std::list<std::string> vec);

        static bool toBool(const char* str);

        //
        // check and tests
        //

        static bool startsWith(const char*  fullString, const char*  startString); 
        static bool endsWith(const char *fullString, const char *endString);

    private:

};

#endif // __STRING_UTILS_H__