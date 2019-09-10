#include <stdio.h>
#include <stdlib.h>
#include "StrBuffer.h"
#define UNITY_INCLUDE_SETUP_STUBS  
#define UNITY_WEAK_ATTRIBUTE 

#include "unity.h"


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

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_AcertOk);
	RUN_TEST(test_String);
	RUN_TEST(test_AcertNok);

	StrBuffer buffer = StrBuffer(1);
	buffer.append("a");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.ptr(), buffer.len(), buffer.bufferlen());
	buffer.append("bb");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.ptr(), buffer.len(), buffer.bufferlen());
	buffer.append("cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.ptr(), buffer.len(), buffer.bufferlen());
	buffer.append("DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.ptr(), buffer.len(), buffer.bufferlen());

	buffer.append(5, "111111", "2222222222", "", "4", "555555555555555555555555555555555555555555555");
	printf("buffer:%s, len:%ld, bufferlen:%ld\n", buffer.ptr(), buffer.len(), buffer.bufferlen());

	char* str[10];
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

	const char* file = "test.txt";
	bool ret;
	StrBuffer filebuffer = StrBuffer(file, &ret);
	printf("ref:%d\n", ret);
	printf("filebuffer:%s, len:%ld, bufferlen:%ld\n", filebuffer.ptr(), filebuffer.len(), filebuffer.bufferlen());

	system("pause");

	return UNITY_END();
}