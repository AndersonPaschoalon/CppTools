#include "VectorUtils.h"

std::vector<std::string> VectorUtils::removeDuplicates(const std::vector<std::string>& strVec) 
{
    std::set<std::string> uniqueStrings;
    for (const auto& str : strVec) 
    {
        uniqueStrings.insert(str);
    }

    std::vector<std::string> result(uniqueStrings.begin(), uniqueStrings.end());
    return result;
}


template <typename T>
std::string VectorUtils::toCsv(const std::vector<T>& src, char separator) 
{
    std::ostringstream oss;
    for (size_t i = 0; i < src.size(); ++i) 
    {
        oss << src[i];
        if (i < src.size() - 1) 
        {
            oss << std::string(separator);
        }
    }
    return oss.str();
}

template <typename T>
std::vector<T> VectorUtils::toVec(const std::string& src, char separator) 
{
    std::vector<T> result;
    std::istringstream iss(src);
    std::string token;
    // while (std::getline(iss, token, ',')) 
    while (std::getline(iss, token, separator)) 
    {
        std::istringstream converter(token);
        T value;
        converter >> value;
        result.push_back(value);
    }
    return result;
}
