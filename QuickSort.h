#pragma once
#include "dynamic_array.h"
template <class T>
class QuickSort
{
public:
	QuickSort(dynamic_array<T>* list);
	void Sort(int l, int h);


private:
	dynamic_array<T>* list;
	inline void Swap(T& i, T& j);

	int Partition(int l, int h);

};

