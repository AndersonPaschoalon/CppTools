#pragma once
#ifndef  __CONSOLE__H__
#define __CONSOLE__H__ 1

#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <list>
#include <string>
#include <thread>
#include <mutex>
#include <string>
#include "StrBuffer.h"

const char ERRMSG_POPEN[] = "popen() failed!";
const char ERRMSG_FGETS[] = "fgets() failed!";

class Console
{
public:

	// constructor/destructor
	Console();
	~Console();

	// command console methods
	//int exeBlock(const char* cmd);
	//int exeNonBlock(const char* cmd);
	int get(char* str);
	bool hasFinished();

	// echo methods
	void cat(FILE* in);

	//
	void pwd(char* cmd);

	int const SUCCESS = 0;
	int const ERROR_POPEN = -1;
	int const ERROR_FGETS = -2;

	int const exeBlock(const char* cmd, int strOutLen, char* strOut);
	int const exeBlock(const char* cmd, StrBuffer* strOut);

	int const helperExeBlock(const char* cmd, StrBuffer* cmdOut);
	int  helperExeNonBlock(const char* cmd, char* cmdOut, int& cmdOutLen);

private:
	char* cmdLastOut;
	bool isCmdFinished;
	bool isExecuting;
	int cmdLastReturnCode;
	bool needFree;


};

#endif // ! __CONSOLE__H__
