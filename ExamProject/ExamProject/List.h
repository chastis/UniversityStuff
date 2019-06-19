//take from https://github.com/chastis/MyList
//merged 2 classes into 1 file

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <ostream>

template <class T>
class List;

template <class T>
class Node {
public:
	Node(T);
	Node(T, Node*, Node*);
	friend List<T>;
	template <class T> friend std::ostream& operator<<(std::ostream& cout, List<T>& list);
private:
	T data;
	Node * prev;
	Node * next;
};

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
	template <class T> friend std::ostream& operator<<(std::ostream& cout, List<T>& list);
private:
	Node<T> * head;
	Node<T> * tail;
	int size;
};

#include "List.cpp"
#endif // !LIST_H