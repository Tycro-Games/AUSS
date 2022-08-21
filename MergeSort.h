#pragma once
#include "vector.h"
template <class T>
class MergeSort {
public:
	MergeSort();
	~MergeSort();
	void Init(vector<T>* list);
	void Sort(int l, int h);

	void Merge(int l, int mid, int h);

private:
	vector<T>* list;

};