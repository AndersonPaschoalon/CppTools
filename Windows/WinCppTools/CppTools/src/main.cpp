#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "StrBuffer.h"
#define UNITY_INCLUDE_SETUP_STUBS  
#define UNITY_WEAK_ATTRIBUTE 
#include "unity.h"
#include "INIReader.h"
#define TEST_FILE_STRBUFFER "Test_StrBuffer.txt"

#include "Console.h"

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

int main()
{
	bool test01 = false;
	bool test02 = false;
	bool test03 = false;
	bool test04 = true;
	bool test05 = false;
	bool test06 = false;
	bool test07 = false;
	bool test08 = false;
	bool test09 = false;
	bool test10 = false;
	bool test11 = false;
	bool test12 = false;
	bool test13 = false;
	bool test14 = false;
	bool test15 = false;
	bool test16 = false;
	bool test17 = false;
	bool test18 = false;
	bool test19 = false;
	bool test20 = false;

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
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.pointer(), buffer.len(), buffer.bufferlen());
	buffer.append("bb");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.pointer(), buffer.len(), buffer.bufferlen());
	buffer.append("cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.pointer(), buffer.len(), buffer.bufferlen());
	buffer.append("DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.pointer(), buffer.len(), buffer.bufferlen());

	buffer.appendVaList(5, "111111", "2222222222", "", "4", "555555555555555555555555555555555555555555555");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.pointer(), buffer.len(), buffer.bufferlen());

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
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.pointer(), buffer.len(), buffer.bufferlen());
	for (int i = 0; i < 10; i++)
	{
		delete str[i];
	}
	delete str;

	const char file[] = TEST_FILE_STRBUFFER;
	bool ret;
	StrBuffer filebuffer = StrBuffer(file, &ret);
	printf("ref:%d\n", ret);
	printf("filebuffer:%s, len:%ld, bufferlen:%ld\n", filebuffer.pointer(), filebuffer.len(), filebuffer.bufferlen());

	StrBuffer  testClear = StrBuffer();
	testClear.append("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	printf("testClear before clear:[%s]\n", testClear.pointer());
	testClear.clear();
	printf("testClear before clear:[%s]\n", testClear.pointer());

	StrBuffer  testTrim = StrBuffer();
	testTrim.append("ABCD                 EFGHI\nJK\tL\tM                       N O P Q R S T U         V\nXZ");
	printf("testClear before trim:[%s]\n", testTrim.pointer());
	testTrim.trim();
	printf("testClear after trim:[%s]\n", testTrim.pointer());
	testTrim.clear();
	testTrim.append("ABCDEFGHIJKLMNOPQRSTUVXZ");
	printf("testClear before trim:[%s]\n", testTrim.pointer());
	testTrim.trim();
	printf("testClear before trim:[%s]\n", testTrim.pointer());


	StrBuffer  testUpLow = StrBuffer();
	testUpLow.clear();
	testUpLow.append("ABCDEFGHIJKLmnopqrstuvxz123456789!@#$%¨&*()_");
	printf("testUpLow before:[%s]\n", testUpLow.pointer());
	testUpLow.toUpper();
	printf("upper:[%s]\n", testUpLow.pointer());
	testUpLow.toLower();
	printf("low:[%s]\n", testUpLow.pointer());




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


void test_ConsoleCmdBlock()
{
	int strOutLen = 0;
	StrBuffer* buffer = new StrBuffer();
	const char command[] = "dir";
	Console console = Console();
	console.helperExeBlock(command, buffer);
	printf("command: %s\n", command);
	printf("strOutLen: %d\n", buffer->len());
	printf("strOut: %s\n", buffer->pointer());

	char outVet1[20];
	char outVet2[20000];

	console.exeBlock(command, 20, outVet1);
	console.exeBlock(command, 20000, outVet2);

	delete buffer;

}