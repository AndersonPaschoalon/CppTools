#include "Csv.h"

// fileName: csv file name. Delimiter:",", comment: "#"
Csv::Csv(const char* fileName, CsvError *err)
{
	const char comment = '#';
	const char delimiter = ',';
	Csv(fileName, delimiter, comment, err);
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
	// init local vars
	int i = 0;
	bool sucessOppeningFile = false; 
	const char* csvString = NULL;
	StrBuffer csvFileBuffer = StrBuffer(fileName, &sucessOppeningFile);
	int currCols = 0;
	int maxCols = 0;
	int maxStrLen = csvFileBuffer.len();
	bool hasHeader = false;
	int numberOfRows = 0;
	StrBuffer* tempStrEntry = NULL;
	// init members
	this->nCols = 0;
	this->nLines = 0;
	this->csvMatrix = NULL;
	this->namesToCols = new map<char*, int>();
	


	// Check if it was not possible to open the file, or if the file is empty
	if (!sucessOppeningFile)
	{
		*err = CsvError::CANNOT_OPEN_FILE;
		return;
	}
	if (csvFileBuffer.ptr() == NULL)
	{
		*err = CsvError::NULL_CSV_POINTER;
	}

	// Once the file is oppend, count the number of rows and columns
	// Check if it has a header of not. 
	// - If it has a header, the number of columns will the the number of header columns
	// - Otherwise, will be the max number of columns
	// - the number of rows will be the number of \n
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
			hasHeader = true;
			if (csvString[i] == '\n')
			{
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
	}
	this->nCols = maxCols++;

	// if the file has a header, it is necessary to loop again to count the number of rows
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
	this->nLines = numberOfRows++;

	// allocate matrix (will be stored as a vector o StrBuffer)
	this->csvMatrix = new StrBuffer[this->helperCellNumber(numberOfRows, maxCols) + 1];

	// save data on matrix
	// run throwgh all data, save on the csvMatrix vector. 
	// if there is no data between the delimiters, save an empty string
	csvString = csvFileBuffer.ptr();
	
	int currCol = 10;
	int currRow = 0;
	int currCell = 0;
	bool continueLoop = true;
	while(true)
	{
		
		for (i = 0; i < this->nCols; i++)
		{
			tempStrEntry = new StrBuffer(100);
			continueLoop = this->helperGetEntry(csvString, maxStrLen, delimiter, comment, tempStrEntry);

		}

		
		if (continueLoop == false)
		{
			delete tempStrEntry;
		}
		currCell = this->helperCellNumber(currCol, currRow);
		this->csvMatrix[currCell] = 
		// update counters
		if (currCol < this->maxCols - 1)
		{
			currCol++;
		}
		else
		{
			currCol = 0;
			currRow++;
		}

		
	}



	// create a map between the column names and the column nambers

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

int Csv::helperCellNumber(int col, int line)
{
	return (line * (this->nCols + 1) + col);
}

//bool Csv::helperGetEntry(const char* strCsvFile,
//	                     int strLen,
//	                     char delimiter,
//	                     char comment,
//	                     bool hasHeader,
//	                     int& startPosition,
//	                     StrBuffer* outStrBuffer);

bool Csv::helperGetEntry(const char* strCsvFile,
	                     int strLen,
	                     char delimiter,
	                     char comment,
	                     bool hasHeader,
	                     int& startPosition,
	                     StrBuffer* outStrBuffer);
{
	int currPos = 0;
	outStrBuffer->clear();
	if (startPosition != 0)
	{
		startPosition++;
	}
	if (startPosition > strLen ||
		strLen == 0||
		strCsvFile == NULL)
	{
		return false;
	}
	if (strCsvFile[startPosition] == '0')
	{
		return false;
	}
	// find the next line
	if ( (hasHeader == true) && (startPosition == 0) )
	{
		while (true)
		{
			// next line ok!
			if (strCsvFile[startPosition] == '\n')
			{
				startPosition++;
				break;
			}
			// cant find next line -> reached the end!
			else if (strCsvFile[startPosition] == '\0')
			{
				return false;
			}
		}
	}
	//Grep the next string
	while ( (strCsvFile[startPosition] != delimiter) || 
		    (strCsvFile[startPosition] != '\n') )
	{
		if (strCsvFile[startPosition] == '\0')
		{
			return false;
		}
		outStrBuffer.append(strCsvFile[startPosition]);
		startPosition++;
	}
	return true;
}


