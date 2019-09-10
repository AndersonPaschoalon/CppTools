#include "StrBuffer.h"

StrBuffer::StrBuffer()
{
	this->strSize = 0;
	this->initBufferSize = 50000;
	this->bufferSize = this->initBufferSize;
	this->str = new char[this->initBufferSize];
	memset(this->str, '\0', this->initBufferSize);
}

StrBuffer::StrBuffer(long int size)
{
	this->strSize = 0;
	this->initBufferSize = size + 1; 
	this->bufferSize = this->initBufferSize;
	this->str = new char[this->initBufferSize];
	memset(this->str, '\0', this->initBufferSize);
}

StrBuffer::~StrBuffer()
{
	delete this->str;
}

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

void StrBuffer::append(const char inChar)
{
	char str[2];
	str[0] = inChar;
	str[1] = '\0';
	this->append(str);
}

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

void StrBuffer::append(int count, ...)
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

void StrBuffer::append(int argc, const char* argv[])
{
	int i = 0;
	for (i = 0; i < argc; i++)
	{
		this->append(argv[i]);
	}
}

const char* StrBuffer::ptr()
{
	return this->str;
}

const long int StrBuffer::len()
{
	return this->strSize;
}

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
void const StrBuffer::trim(int outMaxLen, __out char* strTrimmed)
{
	int posStrTrimmed = 0;
	memset(strTrimmed, '\0', outMaxLen);
	if (this->str == NULL)
	{
		return;
	}
	for (int i = 0; i < outMaxLen; i++)
	{
		if (i >= this->strSize)
		{
			break;
		}
		if (this->str[i] != ' ' && this->str[i] != '\n' && this->str[i] != '\r' &&
			this->str[i] != '\t' && this->str[i] != '\v' && this->str[i] != '\f')
		{
			strTrimmed[posStrTrimmed] = this->str[i];
			posStrTrimmed++;
		}
	}
}

// TODO
void const StrBuffer::toUpper(int outMaxLen, __out char* strUp)
{
}

// TODO
void const StrBuffer::toLower(int outMaxLen, __out char* strLow)
{
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
	return true;
}

//TODO
bool const StrBuffer::endsWith(const char* str)
{
	return true;
}

//TODO
void const StrBuffer::replace(const char* pattern, const char* replaceWith)
{
}

//TODO
bool const StrBuffer::contains(const char* str)
{
	return true;
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


