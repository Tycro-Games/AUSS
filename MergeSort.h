#pragma once
#include "vector.h"
class MergeSort {
public:
	MergeSort(vector<int>* list);
	void Sort(int l, int h);
	void Merge(int l, int mid, int h);
private:
	vector<int>* list;
	vector<int> nList;
};