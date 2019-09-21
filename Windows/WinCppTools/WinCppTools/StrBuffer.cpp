#include "StrBuffer.h"

// ok
StrBuffer::StrBuffer()
{
	this->strSize = 0;
	this->initBufferSize = 50000;
	this->bufferSize = this->initBufferSize;
	this->str = new char[this->initBufferSize];
	memset(this->str, '\0', this->initBufferSize);
}

// ok
StrBuffer::StrBuffer(long int size)
{
	this->strSize = 0;
	this->initBufferSize = size + 1; 
	this->bufferSize = this->initBufferSize;
	this->str = new char[this->initBufferSize];
	memset(this->str, '\0', this->initBufferSize);
}

// Ok
StrBuffer::~StrBuffer()
{
	delete[] this->str;
}

// ok
StrBuffer::StrBuffer(const char* filename, bool* success) : StrBuffer()
{
	char c;
	FILE *fptr;
	// Open file 
	fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		*success = false;
		return;
	}

	// Read contents from file 
	c = fgetc(fptr);
	while (c != EOF)
	{
		this->append(c);
		//printf("%c", c);
		c = fgetc(fptr);
	}
	this->append('\0');

	fclose(fptr);
	*success = true;
}

// ok
void StrBuffer::append(const char inChar)
{
	char str[2];
	str[0] = inChar;
	str[1] = '\0';
	this->append(str);
}

// ok
void StrBuffer::append(const char* inStr)
{
	long int newLen = 0;
	long int strLen = 0;
	char* tempStr = NULL;

	if (inStr == NULL)
	{
		return;
	}
	strLen = strlen(inStr);
	if (this->strSize + strLen < this->bufferSize)
	{
		strcat(this->str, inStr);
		this->strSize = strlen(this->str);
	}
	else
	{
		// backup
		tempStr = new char[this->strSize + 1];
		memset(tempStr, '\0', this->strSize + 1);
		strcpy(tempStr, this->str);

		// new string 
		newLen = this->strSize + strLen + this->initBufferSize;
		delete[] this->str;
		this->str = new char[newLen + 1];
		memset(this->str, '\0', newLen + 1);

		// concat
		strcpy(this->str, tempStr);
		strcat(this->str, inStr);

		// update vars
		this->bufferSize = newLen;
		this->strSize = strlen(this->str);

		// free
		delete[] tempStr;
	}
}

// ok
void StrBuffer::appendVaList(int count, ...)
{
	va_list valist;
	int n = 0;
	int i = 0;

	// initialize valist for num number of arguments
	va_start(valist, count);

	for (i = 0; i < count; i++) 
	{
		this->append((char*)va_arg(valist, char*));
	}

	// clean memory reserved for valist
	va_end(valist);
}

// ok
void StrBuffer::append(int argc, char** argv)
{
	int i = 0;
	for (i = 0; i < argc; i++)
	{
		this->append(argv[i]);
	}
}

// ok
const char* StrBuffer::ptr()
{
	return this->str;
}

// ok
const long int StrBuffer::len()
{
	return this->strSize;
}

// ok
const long int StrBuffer::bufferlen()
{
	return this->bufferSize;
}

// erase string
void StrBuffer::clear()
{
	if (this->str == NULL || this->bufferSize == 0)
	{
		return;
	}
	memset(this->str, '\0', this->bufferSize);
}


// remove white spaces
void const StrBuffer::trim()
{
	int i = 0;
	int posStrTrimmed = 0;
	//memset(this->str, '\0', this->bufferlen);
	if (this->str == NULL)
	{
		return;
	}
	for (i = 0; i < this->len(); i++)
	{
		if (i >= this->strSize)
		{
			break;
		}
		if (this->str[i] != ' ' && this->str[i] != '\n' && this->str[i] != '\r' &&
			this->str[i] != '\t' && this->str[i] != '\v' && this->str[i] != '\f')
		{
			this->str[posStrTrimmed] = this->str[i];
			posStrTrimmed++;
		}
	}
	this->append('\0');
	int currPos = posStrTrimmed;
	for (i = posStrTrimmed; i < this->bufferlen(); i++)
	{
		this->str[i] = '\0';
	}
	
}

// TODO
void const StrBuffer::toUpper()
{
	int i = 0;
	if (this->str == NULL || this->len() <= 0)
	{
		return;
	}
	else
	{
		for (i = 0; i < this->len(); i++)
		{
			this->str[i] = toupper(this->str[i]);
		}
	}
}

// TODO
void const StrBuffer::toLower()
{
	int i = 0;
	if (this->str == NULL || this->len() <= 0)
	{
		return;
	}
	else
	{
		for (i = 0; i < this->len(); i++)
		{
			this->str[i] = tolower(this->str[i]);
		}
	}
}

// compare strings
bool const StrBuffer::equals(const char* str)
{
	if (strcmp(str, this->str) == 0)
	{
		return true;
	}
	return false;
}

//TODO
bool const StrBuffer::startsWith(const char* str)
{
	int i = 0;
	int strCmpLen = strlen(str);
	for (i = 0; i < strCmpLen; i++)
	{
		if (i >= this->len() - 1)
		{
			return false;
		}
		if (this->str[i] == str[i])
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

//TODO
bool const StrBuffer::endsWith(const char* str)
{
	int i = 0;
	int strPos = this->len();
	int strCmpLen = strlen(str);
	int startPos = strPos - strCmpLen;
	if (startPos < 0)
	{
		return false;
	}
	else
	{
		for (i = 0; i < strCmpLen; i++)
		{
			if (this->str[startPos + i] != str[i])
			{
				return false;
			}
		}
	}
	return true;
}

//TODO
/*
void const StrBuffer::replace(const char* pattern, const char* replaceWith)
{
	int i = 0;
	int patternLen = 0;
	int startPos = 0;
	int stopPos = 0;
	int currPos = 0;
	bool isMatch = false;
	bool isEmpyt = false;
	StrBuffer strPt1 = StrBuffer();
	StrBuffer strPt2 = StrBuffer();

	if (pattern == NULL)
	{
		return;
	}
	if (replaceWith == NULL)
	{
		isEmpyt = true;
	}
	else if (replaceWith[0] == '\0')
	{
		isEmpyt = true;
	}
	patternLen = strlen(pattern);
	if (patternLen == 0)
	{
		return;
	}
	// calc the pstartPosition 
	for (i = 0; i < this->len(); i++)
	{
		if (currPos == (patternLen - 1) )
		{
			isMatch = true;
			stopPos = i;
			break;
		}
		if (this->str[i] == pattern[currPos])
		{
			if (currPos == 0)
			{
				startPos = i;
			}
			currPos++;
		}
		else
		{
			currPos = 0;
			startPos = 0;
		}
	}
	int firstStrLen = startPos + 1;
	int secondStrLen = this->len() - startPos - patternLen;
	char* strPt1 = new char[firstStrLen];
	char* strPt2 = new char[secondStrLen];
	for (i = 0; i < this->len(); i++)
	{
		if (i < startPos)
		{
			strPt1[i] = this->str[i];
		}
		else if (i > startPos + patternLen)
		{
			strPt2[i] = this->str[i];
		}
	}
	delete this->str;
	int newLen = 0;
	if (isEmpyt == true)
	{
		newLen = firstStrLen + secondStrLen;
	}
	else
	{
		newLen = firstStrLen + secondStrLen + strlen(replaceWith);
	}
	// re-initializes
	this->strSize = 0;
	this->initBufferSize = newLen + 1;
	this->bufferSize = this->initBufferSize;
	this->str = new char[this->initBufferSize];
	memset(this->str, '\0', this->initBufferSize);
	// append new values
	this->appendVaList(3, strPt1, replaceWith, strPt2);

}
*/

//TODO
bool const StrBuffer::contains(const char* str)
{
	int i = 0;
	int strLen = 0;
	int currPos = 0;
	if (str == NULL)
	{
		return false;
	}
	else if (str[0] == '\0')
	{
		return true;
	}
	strLen = strlen(str);
	if (strLen > this->len())
	{
		return false;
	}
	for (i = 0; i < this->len(); i++)
	{
		if (currPos == strLen)
		{
			return true;
		}
		if (this->str[i] == str[i])
		{
			currPos++;
		}
		else
		{
			currPos = 0;
		}
	}
	return false;
}

//TODO
void const StrBuffer::substring(int start, int length, __out char* subString)
{
}

// retuns char on the specified position
char const StrBuffer::at(int index)
{
	if (this->str == NULL ||
		this->bufferSize == 0 ||
		this->strSize == 0 ||
		index >= this->strSize)
	{
		return '\0';
	}
	else
	{
		return this->str[index];
	}
}


