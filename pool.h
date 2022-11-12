#pragma once
#include "dynamic_array.h"
template <class T>
class pool
{
public:
	pool();
	~pool();
	size_t getCount();
	//needs checking before
	T& PopElement();
	void AddElement(T element);
private:
	dynamic_array<T> poolOf;
};

