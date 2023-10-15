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

        static std::string toLower(const char* str);

        static void lTrim(std::string &s);

        static void rTrim(std::string &s);

        static void trim(std::string &s);

        static std::string ltrimCopy(std::string s);

        static std::string rtrimCopy(std::string s);

        static std::string trimCopy(std::string s);

        //
        // type to string operations
        //

        const static std::string toHexString(unsigned long n);

        const static std::string toHexString(unsigned int n);
        
        const static std::string toHexString(unsigned short n);

        const static std::string toString(std::vector<std::string> vec);
        
        const static std::string toString(std::list<std::string> vec);

        const static bool toBool(const char* str);

        //
        // check and tests
        //

        const static bool startsWith(const std::string &fullString, const std::string &startString); 
        const static bool endsWith(const char *fullString, const char *endString);

    private:

};

#endif // __STRING_UTILS_H__