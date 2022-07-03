#pragma once
#include "vector.h"
class QuickSort
{
public:
	QuickSort(vector<int>* list);
	void Sort(int l, int h);


private:
	vector<int>* list;
	inline void Swap(int& i, int& j);

	int Partition(int l, int h);

};

