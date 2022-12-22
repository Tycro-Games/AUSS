#pragma once
#include <vector>

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
	std::vector<T> poolOf;
};
