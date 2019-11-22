#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

template <class T>
class List;

template <class T>
class Node {
public:
	Node(T);
	Node(T, Node*, Node*);
	friend List<T>;
	template <class T> friend ostream& operator<<(ostream& cout, List<T>& list);
private:
	T data;
	Node * prev;
	Node * next;
};

#include "Node.cpp"
#endif // !NODE_H
