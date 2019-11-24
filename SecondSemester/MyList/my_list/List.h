#ifndef LIST_H
#define LIST_H
//#include <iostream>
#include "Node.h"
using namespace std;

template <class T>
class List {
public:
	List();
	void push_back(T data);
	void push_begin(T data);
	void insert(int pos, T data);
	void remove(int pos);
	int length();
	void write();
	T get(int pos);
	void set(int pos, T data);
	T& operator[](int pos);
	template <class T> friend ostream& operator<<(ostream& cout, List<T>& list);
private:
	Node<T> * head;
	Node<T> * tail;
	int size;
};

#include "List.cpp"
#endif // !LIST_H
