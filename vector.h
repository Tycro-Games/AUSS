#pragma once
template <class T>
class vector {
public:
	vector();
	~vector();
	vector(size_t size);
	vector operator [](int const index);

	void push(const T& item);
	int pop();

	void doubleSize();
	void halfSize();

	int find(const T& item);
	void insert(int index, const T& item);
	void remove(const T& item) { //remove all instances
		return;
	}

	int getSize();
	int getCount();
	int get(int const i);

private:
	void resize(size_t size);
	T* arr;
	int size = 0, count = 0;

};


