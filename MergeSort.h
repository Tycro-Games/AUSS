#pragma once
#include "vector.h"
template <class T>
class MergeSort {
public:
	MergeSort(vector<T>* list);
	~MergeSort();
	void Sort(int l, int h);
	void Merge(int l, int mid, int h);
private:
	vector<T>* list;

};