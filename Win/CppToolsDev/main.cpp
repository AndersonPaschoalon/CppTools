// CppToolsDev.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "CppTools.h"

#define TEST_FILE_STRBUFFER            "..\\TestResources\\Test_StrBuffer.txt"
#define TEST_FILE_INI                  "..\\TestResources\\Test_Ini.ini" 

struct record
{
	const char* precision;
	double lat;
	double lon;
	const char* address;
	const char* city;
	const char* state;
	const char* zip;
	const char* country;
};

// Print header
void header(const char* str);
// Unity Testes
void test_AcertOk(void);
void test_AcertNok(void);
void test_String();
// Str Buffer
void test_StrBuffer();
// ini File
void test_Ini();
// Console
void test_ConsoleCmdBlock();
// test json
void test_cjson();
// Create a bunch of objects as demonstration.
static int print_preallocated(cJSON* root);
// Create a bunch of objects as demonstration.
static void create_objects(void);

int main()
{
	bool test01 = false;
	bool test02 = true;
	bool test03 = true;
	bool test04 = true;
	bool test05 = true;
	bool test06 = true;
	bool test07 = true;
	bool test08 = true;
	bool test09 = true;
	bool test10 = true;
	bool test11 = true;
	bool test12 = true;
	bool test13 = true;
	bool test14 = true;
	bool test15 = true;
	bool test16 = true;
	bool test17 = true;
	bool test18 = true;
	bool test19 = true;
	bool test20 = true;

	// unity 
	if (test01)
	{
		header("Unity Tests");
		UNITY_BEGIN();
		RUN_TEST(test_AcertOk);
		RUN_TEST(test_String);
		return UNITY_END();
	}

	// StrBuffer
	if (test02)
	{
		header("StrBuffer");
		test_StrBuffer();
	}

	// Ini
	if (test03)
	{
		header("Ini File");
		test_Ini();
	}

	if (test04)
	{
		header("ConsoleCmdBlock");
		test_ConsoleCmdBlock();
	}

    if (test05)
    {
        header("cJSON");
        test_cjson();
    }
	system("pause");
	return 0;
}

void header(const char* str)
{
	printf("\n");
	printf("########################################################################################\n");
	printf("%s\n", str);
	printf("########################################################################################\n");
}

void test_AcertOk(void)
{
	int a = 2;
	TEST_ASSERT_EQUAL_INT(2, a, "Impossible");
}

void test_AcertNok(void)
{
	int a = 4;
	TEST_ASSERT_EQUAL_INT(2, a, "2 é diferente de 4");
}

void test_String()
{
	char str1[] = "abcde";
	char str2[] = "abcde";
	TEST_ASSERT_EQUAL_STRING(str1, str2, "As strings são diferentes");
}

void test_StrBuffer()
{
	StrBuffer buffer = StrBuffer(1);
	buffer.append("a");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.cStr(), buffer.len(), buffer.bufferlen());
	buffer.append("bb");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.cStr(), buffer.len(), buffer.bufferlen());
	buffer.append("cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.cStr(), buffer.len(), buffer.bufferlen());
	buffer.append("DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.cStr(), buffer.len(), buffer.bufferlen());

	buffer.appendVaList(5, "111111", "2222222222", "", "4", "555555555555555555555555555555555555555555555");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.cStr(), buffer.len(), buffer.bufferlen());

	char** str;
	str = new char* [10];
	for (int i = 0; i < 10; i++)
	{
		str[i] = new char[15];
		sprintf(str[i], "%d", i);
		if (i < 5)
		{
			strcat(str[i], "aaaa");
		}
		else
		{
			strcat(str[i], "bbb");
		}
	}

	buffer.append(10, str);
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.cStr(), buffer.len(), buffer.bufferlen());
	for (int i = 0; i < 10; i++)
	{
		delete str[i];
	}
	delete str;

	const char file[] = TEST_FILE_STRBUFFER;
	bool ret;
	StrBuffer filebuffer = StrBuffer(file, &ret);
	printf("ref:%d\n", ret);
	printf("filebuffer:%s, len:%ld, bufferlen:%ld\n", filebuffer.cStr(), filebuffer.len(), filebuffer.bufferlen());

	StrBuffer  testClear = StrBuffer();
	testClear.append("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	printf("testClear before clear:[%s]\n", testClear.cStr());
	testClear.clear();
	printf("testClear before clear:[%s]\n", testClear.cStr());

	StrBuffer  testTrim = StrBuffer();
	testTrim.append("ABCD                 EFGHI\nJK\tL\tM                       N O P Q R S T U         V\nXZ");
	printf("testClear before trim:[%s]\n", testTrim.cStr());
	testTrim.trim();
	printf("testClear after trim:[%s]\n", testTrim.cStr());
	testTrim.clear();
	testTrim.append("ABCDEFGHIJKLMNOPQRSTUVXZ");
	printf("testClear before trim:[%s]\n", testTrim.cStr());
	testTrim.trim();
	printf("testClear before trim:[%s]\n", testTrim.cStr());

	StrBuffer  testUpLow = StrBuffer();
	testUpLow.clear();
	testUpLow.append("ABCDEFGHIJKLmnopqrstuvxz123456789!@#$%¨&*()_");
	printf("testUpLow before:[%s]\n", testUpLow.cStr());
	testUpLow.toUpper();
	printf("upper:[%s]\n", testUpLow.cStr());
	testUpLow.toLower();
	printf("low:[%s]\n", testUpLow.cStr());
}

void test_Ini()
{
	INIReader reader(TEST_FILE_INI);
	int parseError = reader.ParseError();
	if (parseError < 0)
	{
		printf("Can't load 'Test_Ini.ini'\n");
	}
	else
	{
		printf("Config loaded from 'test.ini':\n");
		printf("version=%d\n", reader.GetInteger("protocol", "version", -1));
		printf("user:%s\n", reader.Get("user", "name", "UNKNOWN").c_str());
		printf("email=%s\n", reader.Get("user", "email", "UNKNOWN").c_str());
		printf("pi=%f\n", reader.GetReal("user", "pi", -1));
		printf("active=%d\n", reader.GetBoolean("user", "active", true));

		std::cout << "Config loaded from 'test.ini': version="
			<< reader.GetInteger("protocol", "version", -1) << ", name="
			<< reader.Get("user", "name", "UNKNOWN") << ", email="
			<< reader.Get("user", "email", "UNKNOWN") << ", pi="
			<< reader.GetReal("user", "pi", -1) << ", active="
			<< reader.GetBoolean("user", "active", true) << "\n";
	}
}

void test_ConsoleCmdBlock()
{
	int strOutLen = 0;
	StrBuffer* buffer = new StrBuffer();
	const char command[] = "dir";
	Console console = Console();
	console.helperExeBlock(command, buffer);
	printf("command: %s\n", command);
	printf("strOutLen: %d\n", buffer->len());
	printf("strOut: %s\n", buffer->cStr());

	char outVet1[20];
	char outVet2[20000];

	console.exeBlock(command, 20, outVet1);
	console.exeBlock(command, 20000, outVet2);

	delete buffer;

}

void test_cjson()
{
	// print the version
	printf("Version: %s\n", cJSON_Version());

	// Now some samplecode for building objects concisely:
	create_objects();
}

// Create a bunch of objects as demonstration.
static int print_preallocated(cJSON* root)
{
    // declarations 
    char* out = NULL;
    char* buf = NULL;
    char* buf_fail = NULL;
    size_t len = 0;
    size_t len_fail = 0;

    // formatted print 
    out = cJSON_Print(root);

    // create buffer to succeed 
    // the extra 5 bytes are because of inaccuracies when reserving memory 
    len = strlen(out) + 5;
    buf = (char*)malloc(len);
    if (buf == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(1);
    }

    // create buffer to fail 
    len_fail = strlen(out);
    buf_fail = (char*)malloc(len_fail);
    if (buf_fail == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(1);
    }

    // Print to buffer 
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 1)) {
        printf("cJSON_PrintPreallocated failed!\n");
        if (strcmp(out, buf) != 0) {
            printf("cJSON_PrintPreallocated not the same as cJSON_Print!\n");
            printf("cJSON_Print result:\n%s\n", out);
            printf("cJSON_PrintPreallocated result:\n%s\n", buf);
        }
        free(out);
        free(buf_fail);
        free(buf);
        return -1;
    }

    // success 
    printf("%s\n", buf);

    // force it to fail 
    if (cJSON_PrintPreallocated(root, buf_fail, (int)len_fail, 1)) {
        printf("cJSON_PrintPreallocated failed to show error with insufficient memory!\n");
        printf("cJSON_Print result:\n%s\n", out);
        printf("cJSON_PrintPreallocated result:\n%s\n", buf_fail);
        free(out);
        free(buf_fail);
        free(buf);
        return -1;
    }

    free(out);
    free(buf_fail);
    free(buf);
    return 0;
}

// Create a bunch of objects as demonstration. 
static void create_objects(void)
{
    // declare a few. 
    cJSON* root = NULL;
    cJSON* fmt = NULL;
    cJSON* img = NULL;
    cJSON* thm = NULL;
    cJSON* fld = NULL;
    int i = 0;

    // Our "days of the week" array: 
    const char* strings[7] =
    {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };
    // Our matrix: */
    int numbers[3][3] =
    {
        {0, -1, 0},
        {1, 0, 0},
        {0 ,0, 1}
    };
    // Our "gallery" item: 
    int ids[4] = { 116, 943, 234, 38793 };
    // Our array of "records": 
    struct record fields[2] =
    {
        {
            "zip",
            37.7668,
            -1.223959e+2,
            "",
            "SAN FRANCISCO",
            "CA",
            "94107",
            "US"
        },
        {
            "zip",
            37.371991,
            -1.22026e+2,
            "",
            "SUNNYVALE",
            "CA",
            "94085",
            "US"
        }
    };
    volatile double zero = 0.0;

    // Here we construct some JSON standards, from the JSON site. 

    // Our "Video" datatype: */
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
    cJSON_AddItemToObject(root, "format", fmt = cJSON_CreateObject());
    cJSON_AddStringToObject(fmt, "type", "rect");
    cJSON_AddNumberToObject(fmt, "width", 1920);
    cJSON_AddNumberToObject(fmt, "height", 1080);
    cJSON_AddFalseToObject(fmt, "interlace");
    cJSON_AddNumberToObject(fmt, "frame rate", 24);

    // Print to text 
    if (print_preallocated(root) != 0) {
        cJSON_Delete(root);
        exit(EXIT_FAILURE);
    }
    cJSON_Delete(root);

    // Our "days of the week" array: 
    root = cJSON_CreateStringArray(strings, 7);

    if (print_preallocated(root) != 0) {
        cJSON_Delete(root);
        exit(EXIT_FAILURE);
    }
    cJSON_Delete(root);

    // Our matrix: */
    root = cJSON_CreateArray();
    for (i = 0; i < 3; i++)
    {
        cJSON_AddItemToArray(root, cJSON_CreateIntArray(numbers[i], 3));
    }

    // cJSON_ReplaceItemInArray(root, 1, cJSON_CreateString("Replacement")); 

    if (print_preallocated(root) != 0) {
        cJSON_Delete(root);
        exit(EXIT_FAILURE);
    }
    cJSON_Delete(root);

    // Our "gallery" item: 
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "Image", img = cJSON_CreateObject());
    cJSON_AddNumberToObject(img, "Width", 800);
    cJSON_AddNumberToObject(img, "Height", 600);
    cJSON_AddStringToObject(img, "Title", "View from 15th Floor");
    cJSON_AddItemToObject(img, "Thumbnail", thm = cJSON_CreateObject());
    cJSON_AddStringToObject(thm, "Url", "http:/*www.example.com/image/481989943");
    cJSON_AddNumberToObject(thm, "Height", 125);
    cJSON_AddStringToObject(thm, "Width", "100");
    cJSON_AddItemToObject(img, "IDs", cJSON_CreateIntArray(ids, 4));

    if (print_preallocated(root) != 0) {
        cJSON_Delete(root);
        exit(EXIT_FAILURE);
    }
    cJSON_Delete(root);

    // Our array of "records": 
    root = cJSON_CreateArray();
    for (i = 0; i < 2; i++)
    {
        cJSON_AddItemToArray(root, fld = cJSON_CreateObject());
        cJSON_AddStringToObject(fld, "precision", fields[i].precision);
        cJSON_AddNumberToObject(fld, "Latitude", fields[i].lat);
        cJSON_AddNumberToObject(fld, "Longitude", fields[i].lon);
        cJSON_AddStringToObject(fld, "Address", fields[i].address);
        cJSON_AddStringToObject(fld, "City", fields[i].city);
        cJSON_AddStringToObject(fld, "State", fields[i].state);
        cJSON_AddStringToObject(fld, "Zip", fields[i].zip);
        cJSON_AddStringToObject(fld, "Country", fields[i].country);
    }

    // cJSON_ReplaceItemInObject(cJSON_GetArrayItem(root, 1), "City", cJSON_CreateIntArray(ids, 4)); 

    if (print_preallocated(root) != 0) {
        cJSON_Delete(root);
        exit(EXIT_FAILURE);
    }
    cJSON_Delete(root);

    root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "number", 1.0 / zero);

    if (print_preallocated(root) != 0) {
        cJSON_Delete(root);
        exit(EXIT_FAILURE);
    }
    cJSON_Delete(root);
}

