#include "QuickSort.h"

template <class T>

void QuickSort<T>::Sort(int l, int h)
{
	if (l < h) {
		int j = Partition(l, h);
		Sort(l, j);
		Sort(j + 1, h);
	}

}
template <class T>

QuickSort<T>::QuickSort(vector<T>* list) :
	list(list)
{

}
template <class T>

void QuickSort<T>::Swap(T& i, T& j)
{
	T aux = i;
	i = j;
	j = aux;
}
template <class T>
int QuickSort<T>::Partition(int l, int h)
{
	int p = static_cast<int>(list->get(l));
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
template class QuickSort<float>;
template class QuickSort<int>;