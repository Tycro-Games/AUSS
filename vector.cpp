#include "vector.h"
#include <math.h>

template<class T>
vector<T>::vector()
{
	resize(16);
}
template<class T>
vector<T>::~vector()
{
	delete[]arr;
}

template<class T>
vector<T>::vector(size_t size)
{
	if (size > 16) {
		auto nextPowerOfTwo = pow(2, ceil(log2(size)));
		resize(nextPowerOfTwo);
	}
	else
		resize(16);

}

template<class T>
vector<T> vector<T>::operator[](int const index)
{
	return arr[index];
}



template<class T>
void vector<T>::push(const T& item)
{
	if (count < size)
		arr[count++] = item;
	else {
		doubleSize();
		arr[count++] = item;
	}
}

template<class T>
void vector<T>::doubleSize()
{
	T* aux = new T[count];
	for (int i = 0; i < count; i++)
		aux[i] = arr[i];
	resize(size * 2);
	for (int i = 0; i < count; i++)
		arr[i] = aux[i];
}

template<class T>
void vector<T>::halfSize()
{
	T* aux = new T[count];
	for (int i = 0; i < count; i++)
		aux[i] = arr[i];
	resize(size / 2);
	for (int i = 0; i < count; i++)
		arr[i] = aux[i];
}

template<class T>
int vector<T>::getSize()
{
	return size;
}

template<class T>
int vector<T>::getCount()
{
	return count;
}

template<class T>
int vector<T>::get(int const i)
{
	if (i >= 0 && i < count)
		return arr[i];

	return -1;
}

template<class T>
int vector<T>::pop()
{
	if (count - 1 == size / 4)
		halfSize();

	return arr[count--];
}

template<class T>
int vector<T>::find(const T& item)
{
	for (int i = 0; i < count; i++) {
		if (arr[i] == item) {
			return arr[i];
		}
	}
	return -1;
}

template<class T>
void vector<T>::insert(int index, const T& item)
{
	if (index == count)
		push(item);
	else {
		if (count == size)
			doubleSize();
		count++;
		T toAdd = arr[index];
		T lastItem;
		for (int i = index + 1; i < count; i++) {
			lastItem = arr[i];
			arr[i] = toAdd;
			toAdd = lastItem;
		}
		arr[index] = item;

	}
}

template<class T>
void vector<T>::resize(size_t size)
{
	{
		arr = new T[size];
		this->size = size;
	}
}
template class vector<int>;