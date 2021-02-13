#include "cppfunctions.h"

// to compile on Windows to correct the error:
// Error	C4996	'strdup': The POSIX name for this item is deprecated. 
// Instead, use the ISO Cand C++ conformant name : _strdup. 
// See online help for details.
#ifndef _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE 1
#endif // !_CRT_NONSTDC_NO_DEPRECATE


////////////////////////////////////////////////////////////////////////////////
/// STD lib helpers
////////////////////////////////////////////////////////////////////////////////

void string2charvet(const std::string s, char* vetc)
{
	strncpy(vetc, s.c_str(), sizeof(char) * CHAR_BUFFER);
	vetc[sizeof(char) * CHAR_BUFFER - 1] = '\0';
}

void vector2str(std::vector<double> theVec, char* str)
{

	std::list<double> theList;
	std::copy(theVec.begin(), theVec.end(), std::back_inserter(theList));
	list2str(theList, str);

}

void vector2str(std::vector<int> theVec, char* str)
{

	std::list<int> theList;
	std::copy(theVec.begin(), theVec.end(), std::back_inserter(theList));
	list2str(theList, str);

}

void vector2str(std::vector<long int> theVec, char* str)
{

	std::list<long int> theList;
	std::copy(theVec.begin(), theVec.end(), std::back_inserter(theList));
	list2str(theList, str);

}

void vector2str(std::vector<uint> theVec, char* str)
{

	std::list<uint> theList;
	std::copy(theVec.begin(), theVec.end(), std::back_inserter(theList));
	list2str(theList, str);

}

void vector2str(std::vector<unsigned long int> theVec, char* str)
{

	std::list<unsigned long int> theList;
	std::copy(theVec.begin(), theVec.end(), std::back_inserter(theList));
	list2str(theList, str);

}

void list2str(std::list<double> theList, char* str)
{
	str[0] = '\0';
	char buffer[CHAR_BUFFER] = "\0";
	for (std::list<double>::iterator it = theList.begin(); it != theList.end();)
	{
		//std::string val = to_string(*it);
		sprintf(buffer, "%.8f", *it);
		strcat(str, buffer);
		it++;
		if (it != theList.end())
		{
			strcat(str, ",");
		}

	}
}

void list2str(std::list<int> theList, char* str)
{

	str[0] = '\0';
	char buffer[CHAR_BUFFER] = "\0";
	for (std::list<int>::iterator it = theList.begin(); it != theList.end();)
	{
		//std::string val = to_string(*it);
		sprintf(buffer, "%d", *it);
		strcat(str, buffer);
		it++;
		if (it != theList.end())
		{
			strcat(str, ",");
		}

	}

}

void list2str(std::list<long int> theList, char* str)
{

	str[0] = '\0';
	char buffer[CHAR_BUFFER] = "\0";
	for (std::list<long int>::iterator it = theList.begin();
		it != theList.end();)
	{
		//std::string val = to_string(*it);
		sprintf(buffer, "%ld", *it);
		strcat(str, buffer);
		it++;
		if (it != theList.end())
		{
			strcat(str, ",");
		}

	}

}

void list2str(std::list<uint> theList, char* str)
{
	str[0] = '\0';
	char buffer[CHAR_BUFFER] = "\0";
	for (std::list<uint>::iterator it = theList.begin(); it != theList.end();)
	{
		sprintf(buffer, "%d", *it);
		strcat(str, buffer);
		it++;
		if (it != theList.end())
		{
			strcat(str, ",");
		}

	}

}

void list2str(std::list<unsigned long int> theList, char* str)
{

	str[0] = '\0';
	char buffer[CHAR_BUFFER] = "\0";
	for (std::list<unsigned long int>::iterator it = theList.begin();
		it != theList.end();)
	{
		sprintf(buffer, "%ld", *it);
		strcat(str, buffer);
		it++;
		if (it != theList.end())
		{
			strcat(str, ",");
		}
	}
}

void charvet2type(const char* vetc, uint& v)
{
	sscanf(vetc, "%d", &v);
}

void charvet2type(const char* vetc, int& v)
{
	sscanf(vetc, "%d", &v);
}

void charvet2type(const char* vetc, long int& v)
{
	sscanf(vetc, "%ld", &v);
}

void charvet2type(const char* vetc, unsigned long int& v)
{
	sscanf(vetc, "%ld", &v);
}

void charvet2type(const char* vetc, double& v)
{
	sscanf(vetc, "%lf", &v);
}

void charvet2type(const char* vetc, std::list<double>& theList)
{

	//char in_cstr[CHAR_BUFFER] = "1,223,3;4 5555 6";
	char buffer[CHAR_BUFFER];
	double val_buffer = 0;

	int buffer_conter = 0;
	int in_conter = 0;
	int out_conter = 0;

	if (strcmp(vetc, "") == 0)
	{
		return;
	}

	while (1)
	{
		if (delimiter(vetc[in_conter]) || (vetc[in_conter] == '\0'))
		{
			buffer[buffer_conter] = '\0';
			buffer_conter = 0;
			sscanf(buffer, "%lf", &val_buffer);
			theList.push_back(val_buffer);
			out_conter++;
			buffer[0] = '\0';
		}
		else
		{

			buffer[buffer_conter] = vetc[in_conter];
			buffer_conter++;
		}

		if (vetc[in_conter] == '\0')
			break;
		else
			in_conter++;
	}

}

void charvet2type(const char* vetc, std::list<int>& theList)
{

	char buffer[CHAR_BUFFER];
	int val_buffer = 0;

	int buffer_conter = 0;
	int in_conter = 0;
	int out_conter = 0;

	while (1)
	{
		if (delimiter(vetc[in_conter]) || (vetc[in_conter] == '\0'))
		{
			buffer[buffer_conter] = '\0';
			buffer_conter = 0;
			sscanf(buffer, "%d", &val_buffer);
			theList.push_back(val_buffer);
			out_conter++;
			buffer[0] = '\0';
		}
		else
		{

			buffer[buffer_conter] = vetc[in_conter];
			buffer_conter++;
		}

		if (vetc[in_conter] == '\0')
			break;
		else
			in_conter++;
	}

}

void charvet2type(const char* vetc, std::list<long int>& theList)
{

	char buffer[CHAR_BUFFER];
	long int val_buffer = 0;

	int buffer_conter = 0;
	int in_conter = 0;
	int out_conter = 0;

	while (1)
	{
		if (delimiter(vetc[in_conter]) || (vetc[in_conter] == '\0'))
		{
			buffer[buffer_conter] = '\0';
			buffer_conter = 0;
			sscanf(buffer, "%ld", &val_buffer);
			theList.push_back(val_buffer);
			out_conter++;
			buffer[0] = '\0';
		}
		else
		{

			buffer[buffer_conter] = vetc[in_conter];
			buffer_conter++;
		}

		if (vetc[in_conter] == '\0')
			break;
		else
			in_conter++;
	}

}

void charvet2type(const char* vetc, std::list<uint>& theList)
{

	char buffer[CHAR_BUFFER];
	int val_buffer = 0;

	int buffer_conter = 0;
	int in_conter = 0;
	int out_conter = 0;

	while (1)
	{
		if (delimiter(vetc[in_conter]) || (vetc[in_conter] == '\0'))
		{
			buffer[buffer_conter] = '\0';
			buffer_conter = 0;
			sscanf(buffer, "%d", &val_buffer);
			theList.push_back(unsigned(val_buffer));
			out_conter++;
			buffer[0] = '\0';
		}
		else
		{

			buffer[buffer_conter] = vetc[in_conter];
			buffer_conter++;
		}

		if (vetc[in_conter] == '\0')
			break;
		else
			in_conter++;
	}

}

void charvet2type(const char* vetc, std::vector<long int>& theVector)
{
	std::list<long int> theList;
	charvet2type(vetc, theList);
	std::copy(theList.begin(), theList.end(), std::back_inserter(theVector));
}

void charvet2type(const char* vetc, std::vector<int>& theVector)
{
	std::list<int> theList;
	charvet2type(vetc, theList);
	std::copy(theList.begin(), theList.end(), std::back_inserter(theVector));
}

void charvet2type(const char* vetc, std::vector<double>& theVector)
{
	std::list<double> theList;
	charvet2type(vetc, theList);
	std::copy(theList.begin(), theList.end(), std::back_inserter(theVector));
}

void charvet2type(const char* vetc, std::vector<uint>& theVector)
{
	std::list<uint> theList;
	charvet2type(vetc, theList);
	std::copy(theList.begin(), theList.end(), std::back_inserter(theVector));
}

template<typename T>
void printList(std::list<T>& theList)
{
	std::cout << "[";
	for (typename std::list<int>::iterator it = theList.begin();
		it != theList.end(); it++)
	{
		std::cout << *it << ", ";
	}
	std::cout << "]" << std::endl;
}

void printList(std::list<double>& theList)
{
	std::cout << "[";
	for (std::list<double>::iterator it = theList.begin(); it != theList.end();
		it++)
	{
		std::cout << std::setprecision(10) << *it << ", ";
	}
	std::cout << "]" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
/// Math helpers
////////////////////////////////////////////////////////////////////////////////

// bool isEqual(double a, double b, double epsilon = 0.001)
bool isEqual(double a, double b, double epsilon)
{
	return std::abs(a - b) < epsilon;
}

void cumulativeDistribution(std::list<double>& dataSample,
	std::list<double>* cumulativeDat)
{
	uint i = 0;
	double cVal = 0;

	for (std::list<double>::iterator it = dataSample.begin();
		it != dataSample.end(); it++)
	{
		if (i == 0)
		{
			cVal = *it;
			cumulativeDat->push_back(cVal);
			i++;
		}
		else
		{
			cVal = cVal + *it;
			cumulativeDat->push_back(cVal);
		}
	}
}

void scalar_product(std::list<double>& theList, double scalar)
{

	for (std::list<double>::iterator it = theList.begin(); it != theList.end();
		it++)
	{
		*it = (*it) * scalar;
	}
}


////////////////////////////////////////////////////////////////////////////////
/// File helpers
////////////////////////////////////////////////////////////////////////////////

#ifndef  WIN32

bool isFileEmpty(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

#endif // ! WIN


////////////////////////////////////////////////////////////////////////////////
/// Parsers
////////////////////////////////////////////////////////////////////////////////

char** str_split(char* a_str, const char a_delim)
{
	char** result = 0;
	size_t count = 0;
	char* tmp = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	while (*tmp)
	{
		if (a_delim == *tmp)
		{
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	/* Add space for trailing token. */
	count += last_comma < (a_str + strlen(a_str) - 1);

	/* Add space for terminating null std::string so caller
	 knows where the list of returned strings ends. */
	count++;

	result = (char**)malloc(sizeof(char*) * count);
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("*Error*: Memory allocation failed @ str_split()");
		exit(-1);
	}

	if (result)
	{
		size_t idx = 0;
		char* token = strtok(a_str, delim);

		while (token)
		{
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}

bool delimiter(char c)
{
	if (delimiter(c, ',') || delimiter(c, ';') || (delimiter(c, ' ')))
	{
		return true;
	}
	else
	{
		return (false);
	}
}

bool delimiter(char c, const char& d)
{
	if (c == d)
	{
		return (true);
	}
	return (false);
}

////////////////////////////////////////////////////////////////////////////////
/// Process helpers
////////////////////////////////////////////////////////////////////////////////

#ifndef WIN32

FILE* popen2(string command, string type, int& pid)
{
	pid_t child_pid;
	int fd[2];
	pipe(fd);

	if ((child_pid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}

	/* child process */
	if (child_pid == 0)
	{
		if (type == "r")
		{
			close(fd[READ]); //Close the READ end of the pipe since the child's fd is write-only
			dup2(fd[WRITE], 1); //Redirect stdout to pipe
		}
		else
		{
			close(fd[WRITE]); //Close the WRITE end of the pipe since the child's fd is read-only
			dup2(fd[READ], 0);   //Redirect stdin to pipe
		}

		setpgid(child_pid, child_pid); //Needed so negative PIDs can kill children of /bin/sh
		execl("/bin/sh", "/bin/sh", "-c", command.c_str(), NULL);
		exit(0);
	}
	else
	{
		if (type == "r")
		{
			close(fd[WRITE]); //Close the WRITE end of the pipe since parent's fd is read-only
		}
		else
		{
			close(fd[READ]); //Close the READ end of the pipe since parent's fd is write-only
		}
	}

	pid = child_pid;

	if (type == "r")
	{
		return fdopen(fd[READ], "r");
	}

	return fdopen(fd[WRITE], "w");
}

int pclose2(FILE* fp, pid_t pid)
{
	int stat;

	fclose(fp);
	while (waitpid(pid, &stat, 0) == -1)
	{
		if (errno != EINTR)
		{
			stat = -1;
			break;
		}
	}

	return stat;
}
#endif // !WIN


////////////////////////////////////////////////////////////////////////////////
/// Tests
////////////////////////////////////////////////////////////////////////////////

void cfunctions_unitytests()
{
	/*
	RegressionTests rt = RegressionTests();
	rt.printHeader("C functions");
	rt.printTestResult("delimiter", test_delimiter());
	rt.printTestResult("charvet2type", test_charvet2type());
	rt.printTestResult("cumulativeDistribution", test_cumulativeDistribution());
	rt.printTestResult("test_list2str", test_list2str());
	rt.printTestResult("test_cumulativeDistribution",
		test_cumulativeDistribution());
	rt.printTestResult("scalar_product", test_scalar_prod());
	*/

}

bool test_delimiter()
{
	if (delimiter('c') == true)
		return (false);

	if (delimiter(',') == false)
		return (false);

	if (delimiter(' ') == false)
		return (false);

	if (delimiter(';') == false)
		return (false);

	if (delimiter('#', '#') == false)
		return (false);

	if (delimiter('-') == true)
		return (false);

	return (true);
}

bool test_charvet2type()
{
	long int v_lint = 0;
	int v_int = 0;
	double v_d = 0;
	char cstr1[CHAR_BUFFER] = "1000";
	char cstr2[CHAR_BUFFER] = "10.01";

	charvet2type(cstr1, v_lint);
	charvet2type(cstr1, v_int);
	charvet2type(cstr2, v_d);

	if ((v_lint + 1) != 1001)
		return (false);
	if ((v_int + 3) != 1003)
		return (false);
	if ((v_d + 2.2) != 12.21)
		return (false);

	std::list<double> aList;
	std::list<int> aListI;
	std::list<long int> aListL;
	std::list<double> aListN;
	char in_cstrI[CHAR_BUFFER] = "1,223,3;4 5555 6";
	char in_cstrD[CHAR_BUFFER] = "1.2,2.23,3.1;4.4 5.555 6.0";
	//char in_cstrN[CHAR_BUFFER] = "";

	double vd[6];
	int vi[6];
	long int vli[6];

	vi[0] = 1;
	vi[1] = 223;
	vi[2] = 3;
	vi[3] = 4;
	vi[4] = 5555;
	vi[5] = 6;

	vli[0] = 1;
	vli[1] = 223;
	vli[2] = 3;
	vli[3] = 4;
	vli[4] = 5555;
	vli[5] = 6;

	vd[0] = 1.2;
	vd[1] = 2.23;
	vd[2] = 3.1;
	vd[3] = 4.4;
	vd[4] = 5.555;
	vd[5] = 6.0;

	//printList (theList);
	charvet2type(in_cstrI, aListI);
	//printList(aListI);

	charvet2type(in_cstrD, aList);
	//printList(aList);

	charvet2type(in_cstrI, aListL);
	//printList(aListL);

	//charvet2type(in_cstrN, aListL);
	//printList(aListN);

	//double
	uint i = 0;
	for (std::list<double>::iterator it = aList.begin(); it != aList.end();
		it++)
	{
		//std::cout << vd[i] << ":" << *it << std::endl;
		if (vd[i] != *it)
		{

			return (false);
		}
		i++;
	}
	//int
	i = 0;
	for (std::list<int>::iterator it = aListI.begin(); it != aListI.end(); it++)
	{
		//std::cout << vi[i] << ":" << *it << std::endl;
		if (vi[i] != *it)
			return (false);
		i++;
	}
	//long int
	i = 0;
	for (std::list<long int>::iterator it = aListL.begin(); it != aListL.end();
		it++)
	{
		//std::cout << vli[i] << ":" << *it << std::endl;
		if (vli[i] != *it)
			return (false);
		i++;
	}

	return (true);

}

bool test_cumulativeDistribution()
{
	//mat M;
	//M.load("data/regression-tests/exp_interarrival_times.txt");

	std::list<double> dlist;
	std::list<time_sec> cdlist;
	char buffer[CHAR_BUFFER] = "\0";
	charvet2type("10.1,10.2,10.3,11,15.5,16.7", dlist);

	cumulativeDistribution(dlist, &cdlist);
	list2str(cdlist, buffer);

	if (strcmp(buffer,
		"10.10000000,20.30000000,30.60000000,41.60000000,57.10000000,73.80000000")
		!= 0)
	{
		return (false);
	}

	//std::cout << "clist: " << buffer << std::endl;

	return (true);
}

bool test_list2str()
{
	char dstr[CHAR_BUFFER];
	char istr[CHAR_BUFFER];
	std::list<double> doublelist;
	std::list<int> intlist;
	charvet2type("10.1,10.2,10.3,11,15.5,16.7", doublelist);
	charvet2type("1,2,3,4,5,6,7,8,9,0", intlist);
	//printList(doublelist);
	list2str(doublelist, dstr);
	list2str(intlist, istr);

	//std::cout << "str len: " << doublelist.size() << std::endl;

	if (strcmp(dstr,
		"10.10000000,10.20000000,10.30000000,11.00000000,15.50000000,16.70000000")
		!= 0)
	{

		return (false);
	}
	if (strcmp(istr, "1,2,3,4,5,6,7,8,9,0") != 0)
	{
		return (false);
	}

	return (true);
}

bool test_scalar_prod()
{
	std::list<double> aList =
	{ 1, 2, 3, 4, 5, 17, 8, 7 };
	std::vector<double> aListdot7 =
	{ 7, 14, 21, 28, 35, 119, 56, 49 };
	std::vector<double> aList7_116 =
	{ 8.1200, 16.2400, 24.3600, 32.4800, 40.6000, 138.0400, 64.9600, 56.8400 };

	//printList(aList);
	scalar_product(aList, 7);
	//printList(aList);

	uint i = 0;
	for (std::list<double>::iterator it = aList.begin(); it != aList.end();
		it++)
	{
		if (aListdot7[i] != *it)
		{
			return (false);
		}
		i++;
	}

	scalar_product(aList, 1.16);
	//printList(aList);
	i = 0;
	for (std::list<double>::iterator it = aList.begin(); it != aList.end();
		it++)
	{

		if (!isEqual(aList7_116[i], *it))
		{
			printList(aList);
			std::cout << "aList7_116[" << i << "]:" << aList7_116[i] << " != "
				<< "aList." << *it << std::endl;
			return (false);
		}
		i++;
	}

	return (true);
}

