#ifndef NODE_CPP
#define NODE_CPP
#include <iostream>
#include "Node.h"
using namespace std;

template <class T>
Node<T>::Node(T data) {
	this->data = data;
	this->prev = NULL;
	this->next = NULL;
}

template <class T>
Node<T>::Node(T data, Node<T> * prev, Node<T> * next) {
	this->data = data;
	this->prev = prev;
	this->next = next;
}



#endif // !NODE_CPP
