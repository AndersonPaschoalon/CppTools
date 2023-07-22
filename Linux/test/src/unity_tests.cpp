#include <assert.h> 
#include "cpptools.h"

void test_trim();
void test_printTable();
void test_csvparser();

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_trim);
    RUN_TEST(test_printTable);
    RUN_TEST(test_csvparser);

    return UNITY_END();
}

void test_printTable()
{
    std::vector<std::string> labels = {"Name", "Age", "Occupation"};
    std::vector<std::vector<std::string>> tableMatrix = {
        {"Alice", "30", "Engineer"},
        {"Bob", "40", "Manager"},
        {"Charlie", "25", "Designer"}
    };

    Console::printTable(labels, tableMatrix);    
}

void test_trim()
{
    const char strA01[] = "         abs";
    const char strA02[] = "abs     ";
    const char strA03[] = "         abs     ";
    const char strA04[] = "abs";
    const char strA[] = "abs";

    std::string trimStr = strA03;
    StringUtils::trim(trimStr);
    TEST_ASSERT_EQUAL_STRING(strA,  trimStr.c_str());
}

void test_csvparser()
{
    CsvParser parser;
    if (parser.load("test/sample.csv") == 0) 
    {
        // Access data using get() and getColumn()
        std::string value = parser.get(3, 0); // get value at row 0, column 1
        std::vector<std::string> column = parser.getColumn("Age");
        std::cout << " parser.get(3, 0) -> " << value << std::endl;
        std::cout << " parser.getColumn(header_name) -> " << std::endl;
        for (int i = 0; i < column.size(); i++)
        {
            std::cout << "[" << i << "] " << column[i] << std::endl;;
        }

        
    } 
    else 
    {
        std::cout << "Error loading file" << std::endl;
    }    
}