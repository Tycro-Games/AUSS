#pragma once
#include "vector.h"
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
	vector<T> poolOf;
};

