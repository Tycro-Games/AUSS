#include "vector.h"
#include <math.h>
#include "Projectile.h"
#include "ExplosionBullet.h"
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
void vector<T>::push_back(const T& item)
{
	if (count < maxSize)
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
	delete[]arr;
	resize((size_t)(maxSize * 2));
	for (int i = 0; i < count; i++)
		arr[i] = aux[i];
}

template<class T>
void vector<T>::halfSize()
{
	T* aux = new T[count];
	for (int i = 0; i < count; i++)
		aux[i] = arr[i];
	delete[]arr;
	resize((size_t)(maxSize / 2));
	for (int i = 0; i < count; i++)
		arr[i] = aux[i];
}

template<class T>
int vector<T>::size()
{
	return maxSize;
}

template<class T>
int vector<T>::getCount()
{
	return count;
}

template<class T>
T vector<T>::get(int const& i)
{
	T toReturn{};
	if (i >= 0 && i < count)
		toReturn = arr[i];


	return toReturn;
}

template<class T>
T vector<T>::pop_back()
{
	int fourthSize = maxSize / 4;
	if (count - 1 == fourthSize && fourthSize > 4)
		halfSize();

	return arr[count--];
}

template<class T>
bool vector<T>::is_empty()
{
	if (maxSize == 0)
		return true;
	return false;
}



template<class T>
int vector<T>::find(const T& item)
{
	for (int i = 0; i < count; i++) {
		if (arr[i] == item) {
			return i;
		}
	}
	return -1;
}


template<class T>
void vector<T>::insert(int index, const T& item)
{
	if (index == count)
		push_back(item);
	else {
		if (count == maxSize)
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
void vector<T>::prepend(const T& item)
{
	insert(0, item);
}

template<class T>
void vector<T>::remove(const T& item)
{
	T* aux = new T[count];
	int newCount = 0;
	int auxIndex = 0;
	for (int i = 0; i < count; i++) {
		if (arr[i] != item) {
			aux[auxIndex++] = arr[i];
			newCount++;
		}
	}

	count = newCount;

	for (int i = 0; i < count; i++) {
		arr[i] = aux[i];
	}
}

template<class T>
void vector<T>::removeAtIndex(const int& index)
{
	count--;
	for (int i = index; i < count; i++) {
		arr[i] = arr[i + 1];
	}
}

template<class T>
void vector<T>::removeAll()
{
	count = 0;
}

template<class T>
void vector<T>::resize(size_t size)
{

	arr = new T[size];
	this->maxSize = size;

}
template class vector<Projectile*>;
template class vector<ExplosionBullet*>;
template class vector<Entity*>;
template class vector<int>;