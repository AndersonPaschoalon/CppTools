#pragma once
class Console
{
public:
	Console();

	int execBlock(const char* cmd);

	int execNonBlock(const char* cmd);

	bool hasCommandFinished();

	int get(char* lastOutput);

private:
	char* cmdLastOutput;
	int cmdReturnCode;
	bool hasCmdFinished;
};

