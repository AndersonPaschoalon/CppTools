#pragma once
#include <list>
#include "StrBuffer.h"


using namespace std;
class Csv
{

public:

	enum CsvError
	{
		CANNOT_OPEN_FILE,
		INVALID_CSV_FORMAT,
		NULL_CSV_POINTER
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
	int maxCols;
	char* csvMatrix;

};

