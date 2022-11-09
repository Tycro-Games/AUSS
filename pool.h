#pragma once
#include "dynamic_array.h"
template <class T>
class pool
{
public:
	pool();
	~pool();
	int getCount();
	//needs checking before
	T& PopElement();
	void AddElement(T element);
private:
	dynamic_array<T> poolOf;
};

