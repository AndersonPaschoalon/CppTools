#include "CsvParser.h"

int CsvParser::load(const char* csv_file) 
{
    std::ifstream file(csv_file);

    if (!file.is_open()) {
        return -1;
    }

    std::string line;
    bool has_headers = false;

    while (std::getline(file, line)) 
    {
        std::vector<std::string> row;
        std::istringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        if (!has_headers && row.size() > 0 && row[0].find("#") == 0) 
        {
            // Parse headers
            has_headers = true;
            for (auto& header : row) {
                if (header.find("#") == 0) {
                    header.erase(0, 1);
                }
                headers_names.push_back(header);
            }
        } else {
            // Parse data
            std::vector<std::string> data_row(headers_names.size());

            for (size_t i = 0; i < row.size() && i < data_row.size(); i++) 
            {
                data_row[i] = row[i];
            }

            data.push_back(data_row);
        }
    }

    file.close();
    return 0;
}

std::string CsvParser::get(int row, int column) 
{
    if (row < 0 || row >= data.size() || column < 0 || column >= headers_names.size()) 
    {
        return "";
    }

    return data[row][column];
}

std::vector<std::string> CsvParser::getColumn(std::string label) 
{
    std::vector<std::string> column;
    int column_index = -1;

    for (size_t i = 0; i < headers_names.size(); i++) 
    {
        printf("%s\n"), headers_names[i].c_str();
        if (headers_names[i] == label) {
            column_index = i;
            break;
        }
    }

    if (column_index == -1) {
        return column;
    }

    for (size_t i = 0; i < data.size(); i++) 
    {
        if (column_index < data[i].size()) {
            column.push_back(data[i][column_index]);
        } else {
            column.push_back("");
        }
    }

    return column;
}
