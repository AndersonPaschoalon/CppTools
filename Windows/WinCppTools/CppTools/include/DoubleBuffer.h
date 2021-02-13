#ifndef __DOUBLE_BUFFER_H__
#define __DOUBLE_BUFFER_H__ 1

#include "Defines.h"

class CPP_TOOLS_API DoubleBuffer
{
	DoubleBuffer();
	~DoubleBuffer();
	DoubleBuffer(int bufferSize);
	int len();
	int bufferLen();
	int ptr();
	double at(int pos);
	bool set(int pos, int val);
	bool set(int pos, double val);
	bool append(int val);
	bool append(double val);
	bool append(double vet[], int vetSize);
	bool append(int vet[], int vetSize);
	bool sortAscending();
	bool sortDescending();
	bool sub(int val);
	bool summ(int val);
	bool product(int val);
	bool div(int val);
	bool sub(int val[], int size);
	bool summ(int val, int size);
	bool product(int val[], int size);
	bool product_element(int val[], int size);
	bool div(int val[], int size);
	void clear();
	void ones();
	void init(int val);

private:
	int defaultBufferSize = 50000;
	int appendStep = 10000;
};

#endif // !__DOUBLE_BUFFER_H__

