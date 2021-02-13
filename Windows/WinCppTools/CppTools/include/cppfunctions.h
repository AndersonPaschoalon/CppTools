#pragma once

#ifndef __CPP_FUNCTIONS_H__
#define __CPP_FUNCTIONS_H__

// std includes
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>

// Windows vs Linux
#ifndef  _WIN32
#include <sys/wait.h>
#else // ! _WIN32
#include "sys/wait.h" 
#endif

// Local include
#include "Defines.h"
#include "Types.h"
#include "Namespaces.h"

#define _TESTS_FLAG 1

////////////////////////////////////////////////////////////////////////////////
/// STD lib helpers
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief
 *
 * @param theVec
 * @param str
 */
CPP_TOOLS_API void vector2str(std::vector<double> theVec, char* str);

/**
 * @brief
 *
 * @param theVec
 * @param str
 */
CPP_TOOLS_API void vector2str(std::vector<int> theVec, char* str);

/**
 * @brief
 *
 * @param theVec
 * @param str
 */
CPP_TOOLS_API void vector2str(std::vector<long int> theVec, char* str);

/**
 * @brief
 *
 * @param theVec
 * @param str
 */
CPP_TOOLS_API void vector2str(std::vector<uint> theVec, char* str);

/**
 * @brief
 *
 * @param theVec
 * @param str
 */
CPP_TOOLS_API void vector2str(std::vector<unsigned long int> theVec, char* str);

/**
 * @brief Convert a string s to a C string vetc (char vector).
 * Convet a std::string to a C string. The C string must have been
 * instantiated. If the std::string s is larger than the C sting vetc, it is
 * truncated.
 *
 * @param s	 	std::string to be converted
 * @param vetc 	C string output
 */
CPP_TOOLS_API void string2charvet(const std::string s, char* vetc);

/**
 * @brief
 *
 * @param theList
 * @param str
 */
CPP_TOOLS_API void list2str(std::list<double> theList, char* str);

/**
 * @brief
 *
 * @param theList
 * @param str
 */
CPP_TOOLS_API void list2str(std::list<int> theList, char* str);

/**
 * @brief
 *
 * @param theList
 * @param str
 */
CPP_TOOLS_API void list2str(std::list<long int> theList, char* str);

/**
 * @brief
 *
 * @param theList
 * @param str
 */
CPP_TOOLS_API void list2str(std::list<uint> theList, char* str);

/**
 *
 * @param theList
 * @param str
 */
CPP_TOOLS_API void list2str(std::list<unsigned long int> theList, char* str);

/**
 * @brief
 *
 * @param theList
 * @param str
 */
template<typename T>
CPP_TOOLS_API void list2str(std::list<T> theList, std::string str);

/**
 * @brief Convert a integer written in a C string format to int type.
 *
 * @param vetc 	C string integer
 * @param v 	integer output
 */
CPP_TOOLS_API void charvet2type(const char* vetc, int& v);

/**
 * @brief
 *
 * @param vetc
 * @param v
 */
CPP_TOOLS_API void charvet2type(const char* vetc, uint& v);

/**
 * @brief Convert a integer written in a C string format to long int type.
 *
 * @param vetc	C string integer
 * @param v		long int integer output
 */
CPP_TOOLS_API void charvet2type(const char* vetc, long int& v);

/**
 * @brief Convert a integer written in a C string format to long int type.
 *
 * @param vetc	C string integer
 * @param v		long int integer output
 */
CPP_TOOLS_API void charvet2type(const char* vetc, unsigned long int& v);

/**
 * @brief Convert a float number written in a C string format to double type.
 *
 * @param vetc		C string float
 * @param theList	double output
 */
CPP_TOOLS_API void charvet2type(const char* vetc, double& v);

/**
 * @brief Convert a list of floats in CSV format to a std::std::list<double>
 * Takes as input a C string list of integers in CSV format (numbers separated
 * by comma ) and converts it to a std::std::list<double>
 *
 * @param vetc		C string of integers in CSV format
 * @param theList	an empty list in the format std::std::list<double>
 */
CPP_TOOLS_API void charvet2type(const char* vetc, std::list<double>& theList);

/**
 * @brief Convert a list of integer in CSV format to a std::std::list<int>
 * Takes as input a C string list of integers in CSV format (numbers separated
 * by comma ) and converts it to a std::std::list<int>
 *
 * @param vetc		C string of integers in CSV format
 * @param theList	an empty list in the format std::std::list<int>
 */
CPP_TOOLS_API void charvet2type(const char* vetc, std::list<int>& theList);

/**
 * @brief Convert a list of integer in CSV format to a std::std::list<long int>
 * Takes as input a C string list of integers in CSV format (numbers separated
 * by comma ) and converts it to a std::std::list<long int>
 *
 * @param vetc		C string of integers in CSV format
 * @param theList	an empty list in the format std::std::list<long int>
 */
CPP_TOOLS_API void charvet2type(const char* vetc, std::list<long int>& theList);

/**
 * @brief Convert a list of integer in CSV format to a std::std::list<uint>
 * Takes as input a C string list of integers in CSV format (numbers separated
 * by comma ) and converts it to a std::std::list<unsigned  int>
 *
 * @param vetc		C string of integers in CSV format
 * @param theList	an empty list in the format std::std::list<long int>
 */
CPP_TOOLS_API void charvet2type(const char* vetc, std::list<uint>& theList);

CPP_TOOLS_API void charvet2type(const char* vetc, std::vector<long int>& theVector);

CPP_TOOLS_API void charvet2type(const char* vetc, std::vector<int>& theVector);

CPP_TOOLS_API void charvet2type(const char* vetc, std::vector<uint>& theVector);

CPP_TOOLS_API void charvet2type(const char* vetc, std::vector<double>& theVector);

/**
 * @brief Pint a list of any type in the standard output.
 * @param theList
 */
template<typename T>
CPP_TOOLS_API void printList(std::list<T>& theList);

/**
 *
 * @param theList
 */
CPP_TOOLS_API void printList(std::list<double>& theList);

////////////////////////////////////////////////////////////////////////////////
/// File helpers
////////////////////////////////////////////////////////////////////////////////

#ifndef  WIN32

/**
 * @brief Test if the text file being read is empty
 *
 * @param pFile text file
 * @return true if it is empty, false otherwise
 */
CPP_TOOLS_API bool isFileEmpty(std::ifstream& pFile);

#endif // WIN32


////////////////////////////////////////////////////////////////////////////////
/// Math helpers
////////////////////////////////////////////////////////////////////////////////

 /**
  *
  * @param dataSample
  * @param cumulativeDat
  */
CPP_TOOLS_API void cumulativeDistribution(std::list<double>& dataSample,
	std::list<double>* cumulativeDat);

CPP_TOOLS_API void scalar_product(std::list<double>& theList, double scalar);

CPP_TOOLS_API bool isEqual(double a, double b, double epsilon = 0.001);

////////////////////////////////////////////////////////////////////////////////
/// Process helpers
////////////////////////////////////////////////////////////////////////////////

#ifndef  _WIN32

/**
 *
 * @param command
 * @param type
 * @param pid
 * @return
 */
CPP_TOOLS_API FILE* popen2(string command, string type, int& pid);


/**
 *
 * @param fp
 * @param pid
 * @return
 */
CPP_TOOLS_API int pclose2(FILE* fp, pid_t pid);

#endif //_WIN32

////////////////////////////////////////////////////////////////////////////////
/// Parsers
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief check if the character c is a delimiter. Delimiters default are ',',
 * ';' and ' '(white space).
 * @param c char to be tested
 * @return true if it is a delimiter
 */
CPP_TOOLS_API bool delimiter(char c);

/**
 * @brief Check if the character c is a delimiter.Demilimiter is specified as
 * second argument.
 * @param c 	char to be tested
 * @param d 	true if it is a delimiter
 * @return
 */
CPP_TOOLS_API bool delimiter(char c, const char& d);

/**
 * @brief  Split a C string into tokens
 * @param a_str
 * @param a_delim
 * @return
 */
CPP_TOOLS_API char** str_split(char* a_str, const char a_delim);

#ifdef _TESTS_FLAG

////////////////////////////////////////////////////////////////////////////////
/// Tests
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief execute unity tests
 */
void cfunctions_unitytests();

/**
 * Uniy test function
 * @return true if succed
 */
bool test_delimiter();

/**
 * Unity test function
 * @return true if succed
 */
bool test_charvet2type();

/**
 * Unity test function
 * @return true if succed
 */
bool test_cumulativeDistribution();

/**
 * Unity test function
 * @return true if succed
 */
bool test_list2str();

/**
 * Unity test function
 * @return true if succed
 */
bool test_scalar_prod();

#endif // _TESTS_FLAG

#endif /* __CPP_FUNCTIONS_H__ */
