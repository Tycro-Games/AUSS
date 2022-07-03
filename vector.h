#pragma once
template <class T>
class vector {
public:
	vector();
	~vector();
	vector(size_t size);


	void push_back(const T& item);
	T pop_back();
	bool is_empty();


	int find(const T& item);
	void insert(int index, const T& item);
	void prepend(const T& item);
	//removes all instances
	void remove(const T& item);
	void removeAtIndex(const int& index);
	void removeAll();

	//gives the number of items it can hold
	int size();
	//give the number of the acutual items that is holding
	int getCount();
	void print();
	T& get(int const& i);


private:
	void doubleSize();
	void halfSize();
	void resize(size_t size);
	T* arr;
	int maxSize = 0, count = 0;

};


