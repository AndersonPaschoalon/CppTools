#include "StringUtils.h"


//std::string StringUtils::toLower(const char *strIn)
//{
//    std::string str(strIn);
//    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
//    return str;
//}

void StringUtils::toLower(std::string &str)
{
    for (char& c : str) {
        c = tolower(c);
    }    
}

void StringUtils::toUpper(std::string &str)
{
    for (char& c : str) {
        c = toupper(c);
    }    
}

std::string StringUtils::toLowerCopy(const char *str)
{
    std::string result(str);
    StringUtils::toLower(result);
    return result;
}

std::string StringUtils::toUpperCopy(const char *str)
{
    std::string result(str);
    StringUtils::toUpper(result);
    return result;
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

const std::string StringUtils::toHexString(unsigned long n)
{
    std::ostringstream ss;
    ss << std::hex << std::uppercase << n;
    return ss.str();
}

const std::string StringUtils::toHexString(unsigned int n)
{
    std::ostringstream ss;
    ss << std::hex << std::uppercase << n;
    return ss.str();
}

const std::string StringUtils::toHexString(unsigned short n)
{
    std::ostringstream ss;
    ss << std::hex << std::uppercase << n;
    return ss.str();
}

const std::string StringUtils::toString(std::vector<std::string> vec)
{
    std::string result;
    for (const auto &str : vec)
    {
        result += str + ", ";
    }
    // Remove the last ", " added
    if (!result.empty())
    {
        result.erase(result.size() - 2);
    }
    return result;
}

const std::string StringUtils::toString(std::list<std::string> vec)
{
    std::string result;
    for (const auto &str : vec)
    {
        result += str + ", ";
    }
    // Remove the last ", " added
    if (!result.empty())
    {
        result.erase(result.size() - 2);
    }
    return result;
}

const bool StringUtils::toBool(const char *str)
{
    // Convert the string to lowercase for case-insensitive comparison
    std::string sStr = str;
    std::string lowercaseStr;
    for (char c : sStr) {
        lowercaseStr += std::tolower(c);
    }

    // Interpret "true", "1" as true, anything else (including empty string) as false
    return (lowercaseStr == "true" || lowercaseStr == "1");
}

const bool StringUtils::startsWith(const std::string &fullString, const std::string &startString)
{
    if (fullString.length() < startString.length()) 
    {
        return false;
    }
    return fullString.substr(0, startString.length()) == startString;
}

const bool StringUtils::endsWith(const char *fullString, const char *endString)
{
    int fullLength = strlen(fullString);
    int endLength = strlen(endString);

    if (fullLength < endLength)
        return 0;

    return (strcmp(fullString + fullLength - endLength, endString) == 0);
}
