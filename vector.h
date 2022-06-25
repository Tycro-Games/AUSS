#pragma once
template <class T>
class vector {
public:
	vector() {};
	vector(int const size) {
		resize(size);
	}


	vector operator [](int const index) {
		return arr[index];
	}

	void push(const T& item) {
		if (count < size)
			arr[count++] = item;
		else {
			doubleSize();
			arr[count++] = item;
		}
	}
	void doubleSize()
	{
		T* aux = new T[size];
		for (int i = 0; i < count; i++)
			aux[i] = arr[i];
		resize(size * 2);
		for (int i = 0; i < count; i++)
			arr[i] = aux[i];
	}
	void halfSize()
	{
		T* aux = new T[size];
		for (int i = 0; i < count; i++)
			aux[i] = arr[i];
		resize(size / 2);
		for (int i = 0; i < count; i++)
			arr[i] = aux[i];
	}
	void resize(int const size) {
		arr = new T[size];
		this->size = size;
	}
	int getSize() {
		return size;
	}
	int getCount() {
		return count;
	}
	int get(int const i) {
		if (i >= 0 && i < count)
			return arr[i];

		return -1;
	}
	int pop() {
		if (count - 1 == size / 4)
			halfSize();

		return arr[count--];
	}
	int find(const T& item) {
		for (int i = 0; i < count; i++) {
			if (arr[i] == item) {
				return arr[i];
			}
		}
		return -1;
	}
	void insert(int index, const T& item) {
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
	void remove(const T& item) {

	}

private:
	T* arr;
	int size = 0, count = 0;
};


