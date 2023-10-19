#ifndef _VECTOR_UTILS_
#define _VECTOR_UTILS_ 1

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <set>

class VectorUtils
{
    public:

        /// @brief Remove duplicate elements from string vector.
        /// @param strVec 
        /// @return 
        static std::vector<std::string> removeDuplicates(const std::vector<std::string>& strVec);

        /// @brief Convert a std vector to a CSV list.
        /// @param src vector of objects, such as int, double or strings.
        /// @param separator CSV separator, default is comma (,)
        /// @return CSV string.
        template <typename T>
        static std::string toCsv(const std::vector<T>& src, char separator);

        /// @brief Convert a CSV string to an std::vector. 
        /// @param src CSV string list.
        /// @param separator CSV separator, default is comma (,)
        /// @return 
        template <typename T>
        std::vector<T> toVec(const std::string& src, char separator);

    private:
};

#endif // _VECTOR_UTILS_