#pragma once
#include "vector.h"
template <class T>
class QuickSort
{
public:
	QuickSort(vector<T>* list);
	void Sort(int l, int h);


private:
	vector<T>* list;
	inline void Swap(T& i, T& j);

	int Partition(int l, int h);

};

