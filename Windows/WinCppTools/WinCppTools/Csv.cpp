#include "Csv.h"

// fileName: csv file name. Delimiter:",", comment: "#"
Csv::Csv(const char* fileName, CsvError *err)
{
	const char comment = '#';
	const char delimiter = ',';
}

// fileName: csv file name. delimiter: csv delimiter comment: "#"
Csv::Csv(const char* fileName, const char delimiter, CsvError *err)
{
	const char comment = '#';
	Csv(fileName, delimiter, comment, err);
}

// fileName: csv file name. delimiter: csv delimiter, comment: comment char
Csv::Csv(const char* fileName, const char delimiter, const char comment, CsvError *err)
{
	// init vars
	int i = 0;
	bool sucessOppeningFile = false; 
	const char* csvString = NULL;
	StrBuffer csvFileBuffer = StrBuffer(fileName, &sucessOppeningFile);
	int currCols = 0;
	int maxCols = 0;
	int maxStrLen = 0;
	bool hasHeader = false;
	int numberOfRows = 0;
	// init members
	this->maxCols = 0;

	if (!sucessOppeningFile)
	{
		*err = CsvError::CANNOT_OPEN_FILE;
		return;
	}
	if (csvFileBuffer.ptr() == NULL)
	{
		*err = CsvError::NULL_CSV_POINTER;
	}

	csvString = csvFileBuffer.ptr();
	for (i = 0; i < csvFileBuffer.len(); i++)
	{
		// check if csv has reached its end
		if (csvString[i] == NULL || csvString[i] == '\0')
		{
			break;
		}

		// Check if first file character is a header marcation. The number oc cols will be defined 
		// by the number of columns on the header plus 1
		if (csvString[0] == comment)
		{
			if (csvString[i] == '\n')
			{
				maxCols = maxCols;
				break;
			}
			if (csvString[i] == delimiter)
			{
				maxCols++;
			}
			continue;
		}
		// Otherwise, the number of cols will be defined by the max number of separators + 1
		if (csvString[i] == delimiter)
		{
			currCols++;
			if (currCols > maxCols)
			{
				maxCols = currCols;
			}
		}
		else if (csvString[i] == '\n')
		{
			numberOfRows++;
			currCols = 0;
		}
		maxCols++;
		this->maxCols = maxCols;

	}
	if (!hasHeader)
	{
		for (i = 0; i < csvFileBuffer.len(); i++)
		{
			// check if csv has reached its end
			if (csvString[i] == NULL || csvString[i] == '\0')
			{
				break;
			}
			if (csvString[i] == '\n')
			{
				numberOfRows++;
			}
		}
	}

	// allocate matrix
	// save data on matrix
}

Csv::~Csv()
{
}

bool Csv::row(int row, list<char*> &listRow)
{
	return true;
}

bool Csv::col(int col, list<char*> &listCol)
{
	return true;
}

bool Csv::col(const char* colName, list<char*> &listCol)
{
	return true;
}

