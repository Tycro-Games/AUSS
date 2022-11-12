#include "dynamic_array.h"

#include "Projectile.h"
#include "ExplosionBullet.h"

#include <iostream>
#include "Enemy.h"
#include "Tilemap.h"
#include "Observer.h"
template<class T>
dynamic_array<T>::dynamic_array()
{
	resize(16);
}
template<class T>
dynamic_array<T>::~dynamic_array()
{
	delete[]arr;
}


template<class T>
dynamic_array<T>::dynamic_array(size_t size)
{
	if (size > 16) {
		size_t nextPowerOfTwo = static_cast<size_t>(pow(2, ceil(log2(size))));
		resize(nextPowerOfTwo);
	}
	else
		resize(16);
}

template<class T>
T& dynamic_array<T>::operator[](const size_t index)
{
	if (index < maxSize)
		return arr[index];
	try {
		throw std::out_of_range("out of range\n");
	}
	catch (std::out_of_range& e) {
		std::cout << e.what();
		return arr[0];
	}

}



template<class T>
void dynamic_array<T>::push_back(const T& item)
{
	if (count < maxSize)
		arr[count++] = item;
	else {

		doubleSize();
		arr[count++] = item;
	}
}

template<class T>
void dynamic_array<T>::push_unique(const T& item)
{
	//if it already in the array skip it
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
void dynamic_array<T>::doubleSize()
{
	T* aux = new T[count];
	for (int i = 0; i < count; i++)
		aux[i] = arr[i];
	delete[]arr;
	resize((size_t)(maxSize * 2));
	for (int i = 0; i < count; i++)
		arr[i] = aux[i];
	delete[]aux;
}

template<class T>
void dynamic_array<T>::halfSize()
{
	T* aux = new T[count];
	for (int i = 0; i < count; i++)
		aux[i] = arr[i];
	delete[]arr;
	resize((size_t)(maxSize / 2));
	for (int i = 0; i < count; i++)
		arr[i] = aux[i];
	delete[]aux;
}

template<class T>
size_t dynamic_array<T>::size()
{
	return maxSize;
}

template<class T>
size_t dynamic_array<T>::getCount()
{
	return count;
}

template<class T>
void dynamic_array<T>::print()
{
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			std::cout << arr[i] << " ";
		}
		std::cout << '\n';
	}
}
template<>
void dynamic_array<Wave>::print()
{
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			std::cout << arr[i].weight << " ";
		}
		std::cout << '\n';
	}
}
template<>
void dynamic_array<Obstacle>::print()
{
}
template<>
void dynamic_array<Tile>::print()
{
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			std::cout << arr[i].x << " ";
			std::cout << arr[i].y << " ";
		}
		std::cout << '\n';
	}
}

template< >
void dynamic_array<Projectile*>::print()
{
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			std::cout << arr[i]->pos.x << " ";
		}
		std::cout << '\n';
	}
}
template< >
void dynamic_array<Collider*>::print()
{
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			std::cout << arr[i]->pos->x << " ";
		}
		std::cout << '\n';
	}
}


template<class T>
void dynamic_array<T>::print(size_t& i, size_t& j)
{
	for (; i <= j; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << '\n';

}
template<>
void dynamic_array<Wave>::print(size_t& i, size_t& j)
{
	for (; i <= j; i++) {
		std::cout << arr[i].weight << " ";
	}
	std::cout << '\n';

}
template<>
void dynamic_array<Obstacle>::print(size_t& i, size_t& j)
{

}
template<>
void dynamic_array<Tile>::print(size_t& i, size_t& j)
{
	for (; i <= j; i++) {
		std::cout << arr[i].x << " ";
		std::cout << arr[i].y << " ";
	}
	std::cout << '\n';
}
template< >
void dynamic_array<Projectile*>::print(size_t& i, size_t& j)
{
	for (; i <= j; i++) {
		std::cout << arr[i]->pos.x << " ";
	}
	std::cout << '\n';
}
template<class T>
T& dynamic_array<T>::get(size_t const& i)
{
	if (i < count)
		return arr[i];
	try {
		throw std::out_of_range("out of range\n");
	}
	catch (std::out_of_range& e) {
		std::cout << e.what();
		return arr[0];
	}

}

template<class T>
T dynamic_array<T>::pop_back()
{
	size_t fourthSize = maxSize / 4;
	if (count - 1 == fourthSize && fourthSize > 4)
		halfSize();

	return arr[count--];
}

template<class T>
bool dynamic_array<T>::is_empty()
{
	if (maxSize == 0)
		return true;
	return false;
}



template<class T>
int dynamic_array<T>::find(const T& item)
{
	for (int i = 0; i < count; i++) {
		if (arr[i] == item) {
			return i;
		}
	}
	return -1;
}
template<>
int dynamic_array<Wave>::find(const Wave& item)
{
	//no need for this
	std::cout << "wave is not defined for this\n";
	return -1;
}
template<>
int dynamic_array<Tile>::find(const Tile& item)
{
	for (int i = 0; i < count; i++) {
		if (arr[i].x == item.x && arr[i].y == item.y) {
			return i;
		}
	}
	return -1;
}

template<class T>
bool dynamic_array<T>::contains(const T& item)
{
	for (int i = 0; i < count; i++) {
		if (arr[i] == item) {
			return true;
		}
	}
	return false;
}
template<>

bool dynamic_array<Wave>::contains(const Wave& item)
{
	std::cout << "wave is not defined for this\n";
	return false;
}
template<>
bool dynamic_array<Tile>::contains(const Tile& item)
{
	for (int i = 0; i < count; i++) {
		if (arr[i].x == item.x && arr[i].y == item.y) {
			return true;
		}
	}
	return false;
}



template<class T>
void dynamic_array<T>::insert(size_t index, const T& item)
{
	if (index == count)
		push_back(item);
	else {
		if (count == maxSize)
			doubleSize();
		count++;
		T toAdd = arr[index];
		T lastItem;
		for (size_t i = index + 1; i < count; i++) {
			lastItem = arr[i];
			arr[i] = toAdd;
			toAdd = lastItem;
		}
		arr[index] = item;
	}
}


template<class T>
void dynamic_array<T>::prepend(const T& item)
{
	insert(0, item);
}

template<class T>
void dynamic_array<T>::remove(const T& item)
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
	delete[]aux;
}
template<>
void dynamic_array<Wave>::remove(const Wave& item)
{
	std::cout << "wave is not defined for this\n";

}

template<>
void dynamic_array<Tile>::remove(const Tile& item)
{
	Tile* aux = new Tile[count];
	int newCount = 0;
	int auxIndex = 0;
	for (int i = 0; i < count; i++) {
		if (arr[i].x == item.x && arr[i].y == item.y) {
			aux[auxIndex++] = arr[i];
			newCount++;
		}
	}

	count = newCount;

	for (int i = 0; i < count; i++) {
		arr[i] = aux[i];
	}
	delete[]aux;
}

template<class T>
void dynamic_array<T>::removeAtIndex(const size_t& index)
{
	if (count == 0)
		return;
	count--;
	for (size_t i = index; i < count; i++) {
		arr[i] = arr[i + 1];
	}
}

template<class T>
void dynamic_array<T>::removeAll()
{
	count = 0;
}

template<class T>
void dynamic_array<T>::resize(size_t size)
{

	arr = new T[size];
	this->maxSize = size;

}
template class dynamic_array<Projectile*>;
template class dynamic_array<ExplosionBullet*>;
template class dynamic_array<Entity*>;
template class dynamic_array<int>;
template class dynamic_array <float>;
template class dynamic_array <size_t>;
template class dynamic_array <Renderable*>;
template class dynamic_array <Updateable*>;
template class dynamic_array <Enemy*>;
template class dynamic_array <Collider*>;
template class dynamic_array <Tile>;
template class dynamic_array <Tile*>;
template class dynamic_array <Moveable*>;
template class dynamic_array <Obstacle*>;
template class dynamic_array <Observer*>;
template class dynamic_array<EnemySpawner*>;
template class dynamic_array<EnemyTypes>;

template class dynamic_array<Wave>;

