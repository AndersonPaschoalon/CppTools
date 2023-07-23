#include <assert.h> 
#include "cpptools.h"

void test_trim();
void test_printTable();
void test_csvparser();
void test_Console_executeCommandBlock();
void test_Console_executeCommandAsync();

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_trim);
    RUN_TEST(test_printTable);
    RUN_TEST(test_csvparser);

    // test
    RUN_TEST(test_Console_executeCommandBlock);
    RUN_TEST(test_Console_executeCommandAsync);

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


void test_Console_executeCommandBlock()
{
    std::string output;
    int status = Console::executeCommandBlock("ls -lahn", output);

    std::cout << "Command status code: " << status << std::endl;
    std::cout << "Command output:" << std::endl << output << std::endl;

    TEST_ASSERT_EQUAL_INT32(0, status);
}

void test_Console_executeCommandAsync()
{
    Console console;

    if (console.executeCommandAsync("ls -lahn")) 
    {
        std::cout << "Command started." << std::endl;
    } else 
    {
        std::cout << "Failed to start command." << std::endl;
    }

    // Wait for the command to finish
    while (!console.hasCommandFinished()) 
    {
        // Do something else while waiting...
        std::cout << "Waiting the execution to be completed, 1ms sleep..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::string output;
    int status = console.commandResponse(output);

    std::cout << "Command status code: " << status << std::endl;
    std::cout << "Command output:" << std::endl << output << std::endl;

    TEST_ASSERT_EQUAL_INT32(0, status); 
}