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

	/**
	 * Defines a string with  with size of 50000.
	 */
	StrBuffer();

	// 

	/**
	 * defines a string with size initSize.
	 * 
	 * \param initSize
	 */
	StrBuffer(long int initSize);

	/**
	 * Loads the content of a text file into a string buffer.
	 * 
	 * \param filename path to the file to be loaded into the string buffer
	 * \param success trtuns true in case of sucess, false otherwise
	 */
	StrBuffer(const char* filename, __out bool* success);

	/**
	 * Desctructor.
	 * 
	 */
	~StrBuffer();

	// 

	/**
	 * Concats a single char on the string.
	 * 
	 * \param inChar
	 */
	void append(const char inChar);

	/**
	 * concat a string to the string buffer. reallocate memory automatically, 
	 * with the number of positions required if the buffer size is not enough.
	 * 
	 * \param str
	 */
	void append(const char* str);

	// 

	/**
	 * Concat a vector of strings on the string buffer. reallocate memory automatically..
	 * 
	 * \param argc
	 * \param argv
	 */
	void append(int argc, char** argv);

	/**
	 * concat "count" strings passed as argument on the string buffer. reallocate memory automatically.
	 * 
	 * \param count
	 * \param 
	 */
	void appendVaList(int count, ...);

	/**
	 * Clean the buffer overwriting it with '\0' chars.
	 * 
	 */
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
	char* cStr();

	// returns the string current lenght
	const long int len();

	// retuns the current lenght of the allocated memory. 
	const long int bufferlen();


private:

	long int initBufferSize;
	long int bufferSize;
	long int strSize;
	char* str;
};

