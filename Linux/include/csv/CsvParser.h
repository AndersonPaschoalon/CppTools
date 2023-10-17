#ifndef __CSV_PARSER_H__
#define __CSV_PARSER_H__ 1

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "../utils/StringUtils.h"

class CsvParser 
{
public:

    CsvParser();

    ~CsvParser();

    std::string toString();

    int load(const char* csv_file);

    int save(const char *fileName);

    void getSize(int& nRows, int& nCols);

    bool getNextLine(std::vector<std::string>& nextLine);

    std::vector<std::string> getHeaders();

    size_t pos(const char* label);

    std::string get(int row, int column);

    std::vector<std::string> getColumn(std::string label);

    std::string getLabel(int colNumber);

    std::vector<std::string> getLine(int lineNumber);

    std::vector<std::string> getColumn(int colNumber);

    /// @brief Delete all the loaded data (but not the headers)
    void clear();

    /// @brief hange the header values
    /// Regularize data according to the number of labels in the header
    /// @param newHeaders 
    void setHeaders(std::vector<std::string> newHeaders);

    /// @brief Append a new line to the data
    /// @param newLine 
    void appendLine(std::vector<std::string> newLine);



private:

    std::vector<std::vector<std::string>> data;
    std::vector<std::string> headers_names;
    size_t lineCounter;

};


#endif // __CSV_PARSER_H__

