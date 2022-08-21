#include "MergeSort.h"
#include "Projectile.h"
template<class T>
MergeSort<T>::MergeSort() :
	list()
{

}
template<class T>
MergeSort<T>::~MergeSort()
{
}
template <class T>
void MergeSort<T>::Init(vector<T>* lis) {
	list = lis;
}
template<class T>
void MergeSort<T>::Sort(int l, int h)
{
	if (l < h) {
		int mid = (l + h) / 2;
		Sort(l, mid);
		Sort(mid + 1, h);
		Merge(l, mid, h);

	}
}


template<class T>
void MergeSort<T>::Merge(int l, int mid, int h)
{
	int i = l, j = mid + 1;
	vector<T> A(16);
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
	/*A.print();
	list->print();*/
}

template<>
void MergeSort<Collider*>::Merge(int l, int mid, int h)
{
	int i = l, j = mid + 1;
	vector<Collider*> A(16);
	while (i <= mid && j <= h) {
		if (list->get(i)->pos->x < list->get(j)->pos->x)
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
	/*A.print();
	list->print();*/
}

template class MergeSort<float>;
template class MergeSort<Projectile*>;
template class MergeSort<Collider*>;
template class MergeSort<int>;

