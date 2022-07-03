#include "QuickSort.h"


void QuickSort::Sort(int l, int h)
{
	if (l < h) {
		int j = Partition(l, h);
		Sort(l, j);
		Sort(j + 1, h);
	}

}

QuickSort::QuickSort(vector<int>* list) :
	list(list)
{

}

void QuickSort::Swap(int& i, int& j)
{
	int aux = i;
	i = j;
	j = aux;
}

int QuickSort::Partition(int l, int h)
{
	int p = list->get(l);
	int i = l, j = h;
	while (i < j) { //compare elements and change them accordingly
		do
		{
			i++;
		} while (list->get(i) <= p);
		do
		{
			j--;
		} while (list->get(j) > p);
		if (i < j)
			Swap(list->get(i), list->get(j));
	}
	Swap(list->get(l), list->get(j));//get the pivot into the right position
	list->print();
	return j; //partition position
}
