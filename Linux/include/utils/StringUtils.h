#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__ 1

#include <iomanip>
#include <sstream>
#include <string>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdio>    // For remove()


class StringUtils
{
    public:

        //
        // String operations
        //

        static std::string toLower(const char* str);

        static void lTrim(std::string &s);

        static void rTrim(std::string &s);

        static void trim(std::string &s);

        static std::string ltrimCopy(std::string s);

        static std::string rtrimCopy(std::string s);

        static std::string trimCopy(std::string s);

        const static std::string toHexString(unsigned long n);

        const static std::string toHexString(unsigned int n);
        
        const static std::string toHexString(unsigned short n);


    private:

};

#endif // __STRING_UTILS_H__