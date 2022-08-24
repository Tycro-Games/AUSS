#include "vector.h"

#include "Projectile.h"
#include "ExplosionBullet.h"

#include <iostream>
#include "Enemy.h"
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
		size_t nextPowerOfTwo =static_cast<size_t>( pow(2, ceil(log2(size))));
		resize(nextPowerOfTwo);
	}
	else
		resize(16);
}

template<class T>
T& vector<T>::operator[](const int index)
{

	if (index < maxSize)
		return arr[index];

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
void vector<T>::push_unique(const T& item)
{
	if (this->find(item) != -1)
		return;
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
void vector<T>::print()
{
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			std::cout << arr[i] << " ";
		}
		std::cout << '\n';
	}
}
template< >
void vector<Projectile*>::print()
{
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			std::cout << arr[i]->pos->x << " ";
		}
		std::cout << '\n';
	}
}
template< >
void vector<Collider*>::print()
{
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			std::cout << arr[i]->pos->x << " ";
		}
		std::cout << '\n';
	}
}


template<class T>
void vector<T>::print(int& i, int& j)
{
	for (; i <= j; i++) {
		std::cout << arr[i]<< " ";
	}
	std::cout << '\n';
}
template< >
void vector<Projectile*>::print(int& i, int& j)
{
	for (; i <= j; i++) {
		std::cout << arr[i]->pos->x << " ";
	}
	std::cout << '\n';
}
template<class T>
T& vector<T>::get(int const& i)
{

	if (i < count)
		return arr[i];


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
bool vector<T>::contains(const T& item)
{
	for (int i = 0; i < count; i++) {
		if (arr[i] == item) {
			return true;
		}
	}
	return false;
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
	if (count == 0)
		return;
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
template class vector <float>;
template class vector <Renderable*>;
template class vector <Updateable*>;
template class vector <Enemy*>;
template class vector <Collider*>;
