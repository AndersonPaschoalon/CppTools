#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "StrBuffer.h"
#define UNITY_INCLUDE_SETUP_STUBS  
#define UNITY_WEAK_ATTRIBUTE 
#include "unity.h"
#include "INIReader.h"
#define TEST_FILE_STRBUFFER "Test_StrBuffer.txt"

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

int main()
{
	// unity 
	header("Unity Tests");
	//UNITY_BEGIN();
	//RUN_TEST(test_AcertOk);
	//RUN_TEST(test_String);
	header("StrBuffer");
	test_StrBuffer();
	//header("Ini File");
	//test_Ini();

	system("pause");
	return 0;
	//return UNITY_END();
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
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.ptr(), buffer.len(), buffer.bufferlen());
	buffer.append("bb");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.ptr(), buffer.len(), buffer.bufferlen());
	buffer.append("cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.ptr(), buffer.len(), buffer.bufferlen());
	buffer.append("DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.ptr(), buffer.len(), buffer.bufferlen());

	buffer.appendVaList(5, "111111", "2222222222", "", "4", "555555555555555555555555555555555555555555555");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.ptr(), buffer.len(), buffer.bufferlen());

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
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.ptr(), buffer.len(), buffer.bufferlen());
	for (int i = 0; i < 10; i++)
	{
		delete str[i];
	}
	delete str;

	const char file[] = TEST_FILE_STRBUFFER;
	bool ret;
	StrBuffer filebuffer = StrBuffer(file, &ret);
	printf("ref:%d\n", ret);
	printf("filebuffer:%s, len:%ld, bufferlen:%ld\n", filebuffer.ptr(), filebuffer.len(), filebuffer.bufferlen());

	StrBuffer  testClear = StrBuffer();
	testClear.append("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	printf("testClear before clear:[%s]\n", testClear.ptr());
	testClear.clear();
	printf("testClear before clear:[%s]\n", testClear.ptr());

	StrBuffer  testTrim = StrBuffer();
	testTrim.append("ABCD                 EFGHI\nJK\tL\tM                       N O P Q R S T U         V\nXZ");
	printf("testClear before trim:[%s]\n", testTrim.ptr());
	testTrim.trim();
	printf("testClear after trim:[%s]\n", testTrim.ptr());
	testTrim.clear();
	testTrim.append("ABCDEFGHIJKLMNOPQRSTUVXZ");
	printf("testClear before trim:[%s]\n", testTrim.ptr());
	testTrim.trim();
	printf("testClear before trim:[%s]\n", testTrim.ptr());


	StrBuffer  testUpLow = StrBuffer();
	testUpLow.clear();
	testUpLow.append("ABCDEFGHIJKLmnopqrstuvxz123456789!@#$%¨&*()_");
	printf("testUpLow before:[%s]\n", testUpLow.ptr());
	testUpLow.toUpper();
	printf("upper:[%s]\n", testUpLow.ptr());
	testUpLow.toLower();
	printf("low:[%s]\n", testUpLow.ptr());




}

void test_Ini()
{
	INIReader reader("Test_Ini.ini");
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