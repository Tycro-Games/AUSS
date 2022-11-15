#pragma once
#include <vector>
template <class T>
class QuickSort
{
public:
	QuickSort(std::vector<T>* list);
	void Sort(int l, int h);


private:
	std::vector<T>* list;
	inline void Swap(T& i, T& j);

	int Partition(int l, int h);

};

