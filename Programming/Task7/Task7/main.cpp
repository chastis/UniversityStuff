#include <iostream>
#include <conio.h>
#include <vector>
#include <chrono>

using namespace std;

template <class T>
struct Data
{
	Data<T>() {
		next = NULL;
	}

	T data;
	Data<T> * next;
};

template <class T>
struct Queue_vector
{
public:
	Queue_vector<T>(int n) {
		//vector<T> head(n);
		size = 0;
		max_size = n;
	}
	void create_empty(int n) {
		vector<T> head(n);
		size = 0;
		max_size = n;
	}
	void enqueue(T data) {
		if (size == max_size) {
			cout << "ERROR :: QUEUE IS FULL\n";
			return;
		}
		head.push_back(data);
		size++;
	}
	bool is_empty() {
		return !size;
	}
	T dequeue() {
		if (is_empty()) {
			cout << "ERROR :: QUEUE IS EMPTY\n";
			return NULL;
		}
		T temp = head[0];
		head.erase(head.begin());
		size--;
		return temp;
	}
	void draw() {
		for (size_t i = 0; i < size; i++) {
			cout << head[i] << " ";
		}
		cout << endl;
	}
	void insertion_sort() // сортировка вставками
	{
		for (int i = 1; i<size; i++)
			for (int j = i; j>0 && head[j - 1] > head[j]; j--) // пока j>0 и элемент j-1 > j, x-массив int
				swap(head[j - 1], head[j]);        // меняем местами элементы j и j-1
	}
	void quick_sort() {
		qsort(0, size - 1);
	}
private:
	void qsort(int b, int e)
	{
		int l = b, r = e;
		T piv = head[(l + r) / 2]; // Опорным элементом для примера возьмём средний
		while (l <= r)
		{
			while (head[l] < piv)
				l++;
			while (head[r] > piv)
				r--;
			if (l <= r)
				swap(head[l++], head[r--]);
		}
		if (b < r)
			qsort(b, r);
		if (e > l)
			qsort(l, e);
	}
	vector<T> head;
	size_t size, max_size;
};

int main() {
	Queue_vector<int> q(10);
	q.enqueue(2);
	q.enqueue(1);
	q.enqueue(3);
	q.enqueue(9);
	q.enqueue(7);
	q.enqueue(8);
	q.enqueue(6);
	q.enqueue(4);
	q.enqueue(5);
	q.draw();
	auto time = chrono::high_resolution_clock::now();
	q.quick_sort();
	cout << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << "ns" << endl;
	q.draw();
	cout << endl << "That's all Folks!" << endl;
	_getch();
	return 0;
}