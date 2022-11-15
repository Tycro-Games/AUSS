#pragma once
#include <vector>
template <class T>
class MergeSort {
public:
	MergeSort();
	~MergeSort();
	void Init(std::vector<T>* list);
	void Sort(size_t l, size_t h);

	void Merge(size_t l, size_t mid, size_t h);

private:
	std::vector<T>* list;

};