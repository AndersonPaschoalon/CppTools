#pragma once
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <string>
#include "Defines.h"

// class to helps c strings manipulation
class CPP_TOOLS_API StrBuffer
{
public:
	// defines a string with  with 50000 char positions 
	StrBuffer();

	// defines a string with initSize position
	StrBuffer(long int initSize);

	// loads the content of a text file into a string buffer
	StrBuffer(const char* filename, __out bool* success);

	// destructor
	~StrBuffer();

	// concats a single char on the string
	void append(const char inChar);

	// concat a string to the string buffer. reallocate memory automatically, with the number of positions is not enough
	void append(const char* str);

	// concat a vector of strings on the string buffer. reallocate memory automatically.
	void append(int argc, char** argv);

	// concat "count" strings passed as argument on the string buffer. reallocate memory automatically.
	void appendVaList(int count, ...);

	// ok!
	void clear();

	// ok!
	void const trim();

	// ok!
	void const toUpper();

	// ok!
	void const toLower();

	//TODO
	bool const equals(const char* str);

	//TODO
	bool const contains(const char* str);

	//TODO
	bool const startsWith(const char* str);

	//TODO
	bool const endsWith(const char* str);

	//TODO
	//void const replace(const char* pattern, const char* replaceWith);

	//TODO
	void const substring(int start, int length, __out char* subString);

	//TODO
	char const at(int index);

	// returns the c string pointer to the string buffer
	char* pointer();

	// returns the string current lenght
	const long int len();

	// retuns the current lenght of the allocated memory. 
	const long int bufferlen();


private:

	// TODO
	/* TESTS
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
	**/


	long int initBufferSize;
	long int bufferSize;
	long int strSize;
	char* str;
};

