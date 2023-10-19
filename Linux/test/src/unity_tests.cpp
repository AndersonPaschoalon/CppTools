#include <assert.h> 
#include <cassert>
#include <iostream>
#include "cpptools.h"


void test_StringUtils_startsWith();
void test_StringUtils_trim();
void test_StringUtils_bool();
void testToLower();
void testToUpper();
void testToLowerCopy();
void testToUpperCopy();

void test_CsvParser_load();
void test_CsvParser_get();
void test_CsvParser_getColumnLabel();
void test_CsvParser_getHeaders();
void test_CsvParser_getLabel();
void test_CsvParser_getLine();
void test_CsvParser_getColumnNumber();
void test_CsvParser_save();

void test_Console_printTable();
void test_Console_executeCommandBlock();
void test_Console_executeCommandAsync();

void test_plog_helloWorld();
void test_plog_custom();

void cleanup();


int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_StringUtils_trim);
    RUN_TEST(test_StringUtils_startsWith);
    RUN_TEST(test_StringUtils_bool);

    RUN_TEST(test_CsvParser_load);
    RUN_TEST(test_CsvParser_get);
    RUN_TEST(test_CsvParser_getColumnLabel);
    RUN_TEST(test_CsvParser_getHeaders);
    RUN_TEST(test_CsvParser_getLabel);
    RUN_TEST(test_CsvParser_getLine);
    RUN_TEST(test_CsvParser_getColumnNumber);
    RUN_TEST(test_CsvParser_save);

    RUN_TEST(test_Console_printTable);
    RUN_TEST(test_Console_executeCommandBlock);
    RUN_TEST(test_Console_executeCommandAsync);

    RUN_TEST(test_plog_helloWorld);
    RUN_TEST(test_plog_custom);

    cleanup();
    return UNITY_END();
}


void cleanup()
{
    system("rm test/csvParserUnityTest.csv");
    system("rm test/Hello.log");
    system("rm test/custom_log.log");
}


//
// CsvParser
//


void test_CsvParser_load()
{
    TEST_HEADER
    CsvParser parser;
    if (parser.load("test/sample.csv") == 0) 
    {
        // Access data using get() and getColumn()
        std::string value = parser.get(3, 0); // get value at row 0, column 1
        std::vector<std::string> column = parser.getColumn("Age");
        std::cout << " parser.get(3, 0) -> " << value << std::endl;
        std::cout << " parser.getColumn('Age') -> " << StringUtils::toString(column);
        std::cout << std::endl;

        
    } 
    else 
    {
        std::cout << "Error loading file" << std::endl;
    }    
}

void test_CsvParser_get()
{
    TEST_HEADER
    CsvParser parser;
    parser.load("./test/sample.csv");

    std::string data = parser.get(2, 1); // Get data at row 2, column 1 (should be "M")
    std::cout << "Data at (2, 1): " << data << std::endl;

    // Add more similar tests for other data points
}

void test_CsvParser_getColumnLabel()
{
    TEST_HEADER
    CsvParser parser;
    parser.load("./test/sample.csv");

    std::vector<std::string> columnData = parser.getColumn("Age");
    std::cout << "Data in column 'Age': " << StringUtils::toString(columnData) << std::endl;

    // Add more similar tests for other columns
}

void test_CsvParser_getHeaders()
{
    TEST_HEADER
    CsvParser parser;
    parser.load("./test/sample.csv");

    std::vector<std::string> headers = parser.getHeaders();
    std::cout << "Headers: " << StringUtils::toString(headers) << std::endl;
}

void test_CsvParser_getLabel()
{
    TEST_HEADER
    CsvParser parser;
    parser.load("./test/sample.csv");

    std::string label = parser.getLabel(3); // Get label for column 3 (should be "Height (in)")
    std::cout << "Label for column 3: " << label << std::endl;

    // Add more similar tests for other columns
}

void test_CsvParser_getLine()
{
    TEST_HEADER
    CsvParser parser;
    parser.load("./test/sample.csv");

    std::vector<std::string> lineData = parser.getLine(1); // Get data from line 1
    std::cout << "Data in line 1: " << StringUtils::toString(lineData) << std::endl;

    // Add more similar tests for other lines
}

void test_CsvParser_getColumnNumber()
{
    TEST_HEADER
    CsvParser parser;
    parser.load("./test/sample.csv");

    std::vector<std::string> columnData = parser.getColumn(4); // Get data from column 4
    std::cout << "Data in column 4: " << StringUtils::toString(columnData) << std::endl;

    // Add more similar tests for other columns
}

void test_CsvParser_save()
{
    TEST_HEADER
    const char fileName[] = "test/csvParserUnityTest.csv";

    // Delete the file if it exists
    remove(fileName);

    CsvParser csvParser;

    // Clear and set headers
    csvParser.clear();
    std::vector<std::string> headers = {"Name", "Sex", "Age", "Height (in)", "Weight (lbs)"};
    csvParser.setHeaders(headers);

    // Add dummy data
    csvParser.appendLine({"Alice", "F", "25", "65", "140"});
    csvParser.appendLine({"Bob", "M", "30", "72", "180"});
    csvParser.appendLine({"Charlie", "M", "35", "68", "160"});
    csvParser.appendLine({"Diana", "F", "28", "62", "120"});

    // Save to file
    int saveResult = csvParser.save(fileName);
    if (saveResult == 0)
    {
        std::cout << "Data saved to csvParserUnityTest.csv successfully." << std::endl;
    }
    else
    {
        std::cerr << "Failed to save data." << std::endl;
    }

    // Check if the file exists
    if (FILE *file = fopen(fileName, "r"))
    {
        fclose(file);
        std::cout << "File csvParserUnityTest.csv exists." << std::endl;
    }
    else
    {
        std::cerr << "File csvParserUnityTest.csv does not exist." << std::endl;
    }    
}


//
// StringUtils
//

void test_StringUtils_trim()
{
    TEST_HEADER
    const char strA01[] = "         abs";
    const char strA02[] = "abs     ";
    const char strA03[] = "         abs     ";
    const char strA04[] = "abs";
    const char strA[] = "abs";

    std::string trimStr = strA03;
    StringUtils::trim(trimStr);
    TEST_ASSERT_EQUAL_STRING(strA,  trimStr.c_str());
}

void test_StringUtils_startsWith()
{
    TEST_HEADER
    const char* fullString = "Hello, World!";
    const char* startString = "Hello";
    bool testRes = StringUtils::startsWith(fullString, startString);
    if (testRes) 
    {
        std::cout << "The full string starts with the start string." << std::endl;
    } 
    else 
    {
        std::cout << "The full string does not start with the start string." << std::endl;
    }
    TEST_ASSERT_EQUAL(true, testRes);
}


void test_StringUtils_bool()
{
    TEST_HEADER
    std::string trueStr = "True";
    std::string falseStr = "False";
    std::string oneStr = "1";
    std::string zeroStr = "0";
    std::string emptyStr = "";

    std::cout << "trueStr as bool: " << std::boolalpha << StringUtils::toBool(trueStr.c_str()) << std::endl; // true
    std::cout << "falseStr as bool: " << std::boolalpha << StringUtils::toBool(falseStr.c_str()) << std::endl; // false
    std::cout << "oneStr as bool: " << std::boolalpha << StringUtils::toBool(oneStr.c_str()) << std::endl; // true
    std::cout << "zeroStr as bool: " << std::boolalpha << StringUtils::toBool(zeroStr.c_str()) << std::endl; // false
    std::cout << "emptyStr as bool: " << std::boolalpha << StringUtils::toBool(emptyStr.c_str()) << std::endl; // true    
}


void testToLower() 
{
    TEST_HEADER
    std::string str = "Hello World";
    StringUtils::toLower(str);
    assert(str == "hello world");
    std::cout << "toLower test passed.\n";
}

void testToUpper() 
{
    TEST_HEADER
    std::string str = "Hello World";
    StringUtils::toUpper(str);
    assert(str == "HELLO WORLD");
    std::cout << "toUpper test passed.\n";
}

void testToLowerCopy()
{
    TEST_HEADER
    const char* str = "Hello World";
    std::string result = StringUtils::toLowerCopy(str);
    assert(result == "hello world");
    std::cout << "toLowerCopy test passed.\n";
}

void testToUpperCopy() 
{
    TEST_HEADER
    const char* str = "Hello World";
    std::string result = StringUtils::toUpperCopy(str);
    assert(result == "HELLO WORLD");
    std::cout << "toUpperCopy test passed.\n";
}



//
// Console
//

void test_Console_printTable()
{
    TEST_HEADER
    std::vector<std::string> labels = {"Name", "Age", "Occupation"};
    std::vector<std::vector<std::string>> tableMatrix = {
        {"Alice", "30", "Engineer"},
        {"Bob", "40", "Manager"},
        {"Charlie", "25", "Designer"}
    };

    Console::printTable(labels, tableMatrix);    
}

void test_Console_executeCommandBlock()
{
    TEST_HEADER
    std::string output;
    int status = Console::executeCommandBlock("ls -lahn", output);

    std::cout << "Command status code: " << status << std::endl;
    std::cout << "Command output:" << std::endl << output << std::endl;

    TEST_ASSERT_EQUAL_INT32(0, status);
}

void test_Console_executeCommandAsync()
{
    TEST_HEADER
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


//
// PLOG
//

void test_plog_helloWorld()
{
    TEST_HEADER
    plog::init(plog::debug, "test/Hello.log"); // Step2: initialize the logger

    // Step3: write log messages using a special macro
    // There are several log macros, use the macro you liked the most

    PLOGD << "Hello log!"; // short macro
    PLOG_DEBUG << "Hello log!"; // long macro
    PLOG(plog::debug) << "Hello log!"; // function-style macro
    
    // Also you can use LOG_XXX macro but it may clash with other logging libraries
    LOGD << "Hello log!"; // short macro
    LOG_DEBUG << "Hello log!"; // long macro
    LOG(plog::debug) << "Hello log!"; // function-style macro    
}

void test_plog_custom()
{
    TEST_HEADER
    plog_easy_init(plog::debug, "test/custom_log.log");
    _PLOG_NONE << "_PLOG_NONE";
    _PLOG_FATAL << "_PLOG_FATAL";
    _PLOG_ERROR << "_PLOG_N_PLOG_ERRORONE";
    _PLOG_WARN << "_PLOG_WARN";
    _PLOG_INFO << "_PLOG_INFO";
    _PLOG_DEBUG << "_PLOG_DEBUG";
    _PLOG_VERBOSE << "_PLOG_VERBOSE";


}





