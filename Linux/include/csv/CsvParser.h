#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class CsvParser 
{
public:
    int load(const char* csv_file);

    std::string get(int row, int column);

    std::vector<std::string> getColumn(std::string label);

private:
    std::vector<std::vector<std::string>> data;
    std::vector<std::string> headers_names;
};




