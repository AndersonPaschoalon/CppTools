#include "CsvParser.h"


CsvParser::CsvParser()
{
    this->lineCounter = 0;
}

CsvParser::~CsvParser()
{
}

std::string CsvParser::toString()
{
    return StringUtils::toString(this->headers_names);
}

int CsvParser::load(const char *csv_file)
{
    FILE* file = fopen(csv_file, "r");
    if (!file) 
    {
        std::cerr << "Error: Could not open file " << csv_file << "\n";
        return -1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) 
    {
        printf("");
        std::vector<std::string> row;
        char* token = strtok(line, ",");
        while (token) 
        {
            std::string strToken = token;
            // clean the string
            StringUtils::trim(strToken);
            // add string 
            row.push_back(strToken);
            token = strtok(nullptr, ",");
        }
        this->data.push_back(row);
    }

    // Assume the first line contains the headers
    if (!this->data.empty()) 
    {
        // check if the first char is a comment
        bool hasHeader = StringUtils::startsWith(data[0][0].c_str(), "#");
        if(hasHeader)
        {
            this->headers_names = this->data[0];
            // Remove headers from data
            this->data.erase(this->data.begin());  
            //std::cout << "headers_names: " << StringUtils::toString(this->headers_names) << std::endl;
            // remove the header marker from the first label
            this->headers_names[0].erase(0, 1);
            // make sure it does not starts with whitespaces
            StringUtils::trim(this->headers_names[0]);
        }
    }

    fclose(file);
    return 0;
}

std::string CsvParser::get(int row, int column)
{
    if (row >= 0 && row < static_cast<int>(this->data.size()) &&
        column >= 0 && column < static_cast<int>(this->data[row].size())) 
        {
        return this->data[row][column];
    }
    return "";
}


std::vector<std::string> CsvParser::getColumn(std::string label)
{
    std::vector<std::string> column;
    int columnIndex = -1;
    for (size_t i = 0; i < headers_names.size(); ++i) 
    {
        if (headers_names[i] == label) {
            columnIndex = static_cast<int>(i);
            break;
        }
    }

    if (columnIndex >= 0) {
        for (const auto& row : this->data) 
        {
            if (columnIndex < static_cast<int>(row.size())) 
            {
                column.push_back(row[columnIndex]);
            }
        }
    }

    return column;
}

std::vector<std::string> CsvParser::getHeaders()
{
    return headers_names;
}

size_t CsvParser::pos(const char *label)
{
    for (size_t i = 0; i < headers_names.size(); ++i) 
    {
        if (headers_names[i] == label) 
        {
            return static_cast<int>(i);
        }
    }
    return -1;  // Label not found
}

std::string CsvParser::getLabel(int colNumber)
{
    if (colNumber >= 0 && colNumber < static_cast<int>(headers_names.size()))
    {
        return headers_names[colNumber];
    }
    else
    {
        return "";
    }       
}

std::vector<std::string> CsvParser::getLine(int lineNumber)
{
    if (lineNumber >= 0 && lineNumber < static_cast<int>(data.size()))
        return data[lineNumber];
    else
        return std::vector<std::string>();
}

std::vector<std::string> CsvParser::getColumn(int colNumber)
{
    std::vector<std::string> column;
    if (colNumber >= 0 && colNumber < static_cast<int>(headers_names.size())) 
    {
        for (const auto& row : data) 
        {
            if (colNumber < static_cast<int>(row.size()))
                column.push_back(row[colNumber]);
        }
    }
    return column;
}

void CsvParser::clear()
{
    this->data.clear();
}

void CsvParser::setHeaders(std::vector<std::string> newHeaders)
{
    this->headers_names = newHeaders;

    // Regularize data according to the number of labels in the header
    for (auto& row : this->data) {
        while (row.size() < newHeaders.size()) 
        {
            row.push_back(""); // Add empty strings for missing elements
        }
        while (row.size() > newHeaders.size()) 
        {
            row.pop_back(); // Delete elements for extra elements
        }
    }
}

void CsvParser::appendLine(std::vector<std::string> newLine)
{
    // Add empty strings for missing elements
    while (newLine.size() < this->headers_names.size()) 
    {
        newLine.push_back("");
    }

    this->data.push_back(newLine);    
}

int CsvParser::save(const char *fileName)
{
    char fileExtension[] = ".csv";
    int fileNameLength = strlen(fileName);
    int extensionLength = strlen(fileExtension);

    // Check if the file name already ends with ".csv"
    bool endsWithCsv = StringUtils::endsWith(fileName, fileExtension);

    // Prepare the complete file name with ".csv" if needed
    char completeFileName[1024];
    if (endsWithCsv == false)
    {
        strcpy(completeFileName, fileName);
        strcat(completeFileName, fileExtension);
    }
    else
    {
        strcpy(completeFileName, fileName);
    }

    FILE *file = fopen(completeFileName, "w");
    if (!file)
    {
        printf("Error: Could not open file %s for writing.\n", completeFileName);
        return -1;
    }

    // Write headers if available
    if (!this->headers_names.empty())
    {
        fprintf(file, "#");
        for (size_t i = 0; i < this->headers_names.size(); ++i)
        {
            fprintf(file, "%s", this->headers_names[i].c_str());
            if (i < this->headers_names.size() - 1)
                fprintf(file, ",");
        }
        fprintf(file, "\n");
    }

    // Write data
    for (const auto &row : this->data)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            fprintf(file, "%s", row[i].c_str());
            if (i < row.size() - 1)
                fprintf(file, ",");
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}

void CsvParser::getSize(int &nRows, int &nCols)
{
    nRows = static_cast<int>(data.size());
    if (headers_names.empty()) 
    {
        if (!data.empty()) 
        {
            nCols = static_cast<int>(data[0].size());
        } 
        else 
        {
            nCols = 0;
        }
    } 
    else 
    {
        nCols = static_cast<int>(headers_names.size());
    }    
}

bool CsvParser::getNextLine(std::vector<std::string> &nextLine)
{
    while(true)
    {
        if (this->lineCounter >= data.size()) 
        {
            return false;  // No more lines
        }

        // check if the line is empty or it has a single element "" (the parser already does trim internally)
        if ((data[this->lineCounter].size() == 0) ||
            ((data[this->lineCounter].size() == 1) && strcmp(data[this->lineCounter][0].c_str(), "") == 0 ))
        {
            ++this->lineCounter;
            continue;
        }

        nextLine = data[this->lineCounter];
        ++this->lineCounter;
        break;
    }

    return true;
}
