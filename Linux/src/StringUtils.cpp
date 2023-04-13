#include "StringUtils.h"


std::string StringUtils::toLower(const char *strIn)
{
    std::string str(strIn);
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
    return str;
}

void StringUtils::lTrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void StringUtils::rTrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void StringUtils::trim(std::string &s)
{
    StringUtils::rTrim(s);
    StringUtils::lTrim(s);
}

std::string StringUtils::ltrimCopy(std::string s)
{
    StringUtils::lTrim(s);
    return s;
}

std::string StringUtils::rtrimCopy(std::string s)
{
    StringUtils::rTrim(s);
    return s;
}

std::string StringUtils::trimCopy(std::string s)
{
    StringUtils::trim(s);
    return s;
}
