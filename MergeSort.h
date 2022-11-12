#pragma once
#include "dynamic_array.h"
template <class T>
class MergeSort {
public:
	MergeSort();
	~MergeSort();
	void Init(dynamic_array<T>* list);
	void Sort(size_t l, size_t h);

	void Merge(size_t l, size_t mid, size_t h);

private:
	dynamic_array<T>* list;

};