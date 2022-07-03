#include "MergeSort.h"

MergeSort::MergeSort(vector<int>* list) :
	list(list)

{

}

void MergeSort::Sort(int l, int h)
{
	if (l < h) {
		int mid = (l + h) / 2;
		Sort(l, mid);
		Sort(mid + 1, h);
		Merge(l, mid, h);

	}
}

void MergeSort::Merge(int l, int mid, int h)
{
	int i = l, j = mid + 1;
	vector<int> A(16);
	while (i <= mid && j <= h) {
		if (list->get(i) < list->get(j))
			A.push_back(list->get(i++));
		else {
			A.push_back(list->get(j++));
		}
	}
	for (; i <= mid; i++)
	{
		A.push_back(list->get(i));
	}
	for (; j <= h; j++)
	{
		A.push_back(list->get(j));
	}
	//copy to the list
	int k = 0;
	for (size_t i = l; i <= h; i++)
	{
		list->get(i) = A.get(k++);
	}
	A.print();
	list->print();
}
