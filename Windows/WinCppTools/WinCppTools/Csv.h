#pragma once
#include <list>
#include <string>
#include <map>
#include "StrBuffer.h"


using namespace std;
class Csv
{

public:

	enum CsvError
	{
		CANNOT_OPEN_FILE,
		INVALID_CSV_FORMAT,
		NULL_CSV_POINTER,
	};

	// fileName: csv file name. Delimiter:",", comment: "#"
	Csv(const char* fileName, CsvError *err);

	// fileName: csv file name. delimiter: csv delimiter comment: "#"
	Csv(const char* fileName, const char delimiter, CsvError *err);

	// fileName: csv file name. delimiter: csv delimiter, comment: comment char
	Csv(const char* fileName, const char delimiter, const char comment, CsvError *err);

	~Csv();

	bool row(int row, list<char*> &listRow);

	bool col(int col, list<char*> &listCol);

	bool col(const char* colName, list<char*> &listCol);


private:

	int nLines;
	int nCols;
	StrBuffer* csvMatrix;
	map<char*, int>* namesToCols;

	/**
	 * Recover the next string between delimiters, in a StrBuffer object.
	 */
	bool helperGetEntry(const char* strCsvFile, 
		                int strLen, 
		                char delimiter, 
		                char comment,
		                bool hasHeader,
		                int& startPosition,
		                StrBuffer* outStrBuffer);

	/**
	 * Helps to calc the position on a linearized matrix. 
	 */
	int helperCellNumber(int col, int line);

};

