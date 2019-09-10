#pragma once
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <string>

// class to helps c strings manipulation
class StrBuffer
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
	void append(int argc, const char* argv[]);

	// concat "count" strings passed as argument on the string buffer. reallocate memory automatically.
	void append(int count, ...);

	// TODO
	void clear();

	// TODO
	void const trim(int outMaxLen, __out char* strTrimmed);

	// TODO
	void const toUpper(int outMaxLen, __out char* strUp);

	// TODO
	void const toLower(int outMaxLen, __out char* strLow);

	//TODO
	bool const equals(const char* str);

	//TODO
	bool const contains(const char* str);

	//TODO
	bool const startsWith(const char* str);

	//TODO
	bool const endsWith(const char* str);

	//TODO
	void const replace(const char* pattern, const char* replaceWith);

	//TODO
	void const substring(int start, int length, __out char* subString);

	//TODO
	char const at(int index);

	// returns the c string pointer to the string buffer
	const const char* ptr();

	// returns the string current lenght
	const const long int len();

	// retuns the current lenght of the allocated memory. 
	const const long int bufferlen();


private:
	long int initBufferSize;
	long int bufferSize;
	long int strSize;
	char* str;
};

