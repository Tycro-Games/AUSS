#pragma once
#include "dynamic_array.h"
template <class T>
class MergeSort {
public:
	MergeSort();
	~MergeSort();
	void Init(dynamic_array<T>* list);
	void Sort(int l, int h);

	void Merge(int l, int mid, int h);

private:
	dynamic_array<T>* list;

};