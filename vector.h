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
			T* aux = new T[size];
			for (int i = 0; i < count; i++)
				aux[i] = arr[i];
			resize(size * 2);
			for (int i = 0; i < count; i++)
				arr[i] = aux[i];
			arr[count++] = item;
		}
	}
	void resize(int const size) {
		arr = new T[size];
		this->size = size;
	}
	int getSize() {
		return size;
	}
	int get(int const i) {
		return arr[i];
	}
private:
	T* arr;
	int size = 0, count = 0;
};


