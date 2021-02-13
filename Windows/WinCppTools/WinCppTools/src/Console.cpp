#include "Console.h"
///////////////////////////////////////////////////////////////////////////////
// Public Methods
///////////////////////////////////////////////////////////////////////////////

Console::Console()
{
	this->cmdLastOut = NULL;
	this->isCmdFinished = true;
	this->cmdLastReturnCode = 0;
	this->needFree = false;
	this->isExecuting = false;
}

Console::~Console()
{
	if (this->needFree)
	{
		delete[] this->cmdLastOut;
		this->cmdLastOut = NULL;
	}
}

int Console::get(char* str)
{
	strcpy(str, this->cmdLastOut);
	return this->cmdLastReturnCode;
}

bool Console::hasFinished()
{
	return this->isCmdFinished;
}

int const Console::exeBlock(const char* cmd, StrBuffer* strOut)
{
	return this->helperExeBlock(cmd, strOut);
}

int const Console::exeBlock(const char* cmd, int strOutLen, char* strOut)
{
	int i = 0;
	int retVal;
	int cmdOutLen = 0;
	int lastChar = strOutLen - 1;
	const char* outPtr = NULL;
	StrBuffer* buffer = new StrBuffer();
	retVal = this->helperExeBlock(cmd, buffer);
	outPtr = buffer->ptr();
	cmdOutLen = buffer->len();
	memset(strOut, '\0', strOutLen);
	
	for (i = 0; i < strOutLen; i++)
	{
		if (i == lastChar)
		{
			strOut[i] = '\0';
			break;
		}
		strOut[i] = outPtr[i];
		if (outPtr[i] == '\0')
		{
			break;
		}
	}


	printf("** command: %s\n", cmd);
	printf("** strOutLen: %d\n", strOutLen);
	printf("** strOut: %s\n", strOut);
	return retVal;

}


///////////////////////////////////////////////////////////////////////////////
// Private Methods
///////////////////////////////////////////////////////////////////////////////

int const Console::helperExeBlock(const char* cmd, StrBuffer* cmdOut)
{
	char buffer[128];
	std::string result = "";
	int msgLen = 0;
	int cmdReturnCode = 0;
	int retCode = 0;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	FILE* pipe = _popen(cmd, "r");
#else
	FILE* pipe = popen(cmd, "r");
#endif
	if (!pipe)
	{
		msgLen = strlen(ERRMSG_POPEN) + 1;
		cmdOut->append(ERRMSG_POPEN);
		return -1;
	}
	else
	{
		try
		{
			while (fgets(buffer, sizeof buffer, pipe) != NULL) {
				result += buffer;
			}
		}
		catch (...)
		{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
			_pclose(pipe);
#else
			pclose(pipe);
#endif
			cmdOut->append(ERRMSG_FGETS);
			return ERROR_FGETS;
		}
		cmdOut->append(result.c_str());
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		retCode = _pclose(pipe);
#else
		retCode = pclose(pipe);
#endif
		return retCode;
	}
}

int Console::helperExeNonBlock(const char* cmd, char* cmdOut, int& cmdOutLen)
{
	// TODO
	return 0;
}

