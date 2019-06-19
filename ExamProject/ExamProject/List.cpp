#ifndef LIST_CPP
#define LIST_CPP

#include "List.h"

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

template <class T>
List<T>::List() {
	head = NULL;
	tail = NULL;
	size = 0;
}

template <class T>
void List<T>::push_back(T data) {
	Node<T> * nd = new Node<T>(data, NULL, NULL);
	if (head) {
		nd->prev = tail;
		tail->next = nd;
		tail = nd;
	}
	else {
		head = nd;
		tail = nd;
	}
	size++;
}

template <class T>
void List<T>::push_begin(T data) {
	Node<T> * nd = new Node<T>(data, NULL, NULL);
	if (head) {
		nd->next = head;
		head->prev = nd;
		head = nd;
	}
	else {
		head = nd;
		tail = nd;
	}
	size++;
}

template <class T>
void List<T>::write() {
	Node<T> * temp = head;
	while (temp) {
		std::cout << temp->data << " ";
		temp = temp->next;
	}

	std::cout << std::endl;
}

template <class T>
std::ostream& operator<<(std::ostream& cout, List<T>& list) {
	Node<T> * temp = list.head;
	while (temp) {
		if (!temp->next) { std::cout << temp->data; }
		else { cout << temp->data << " "; }
		temp = temp->next;
	}
	return cout;
}	

template <class T>
T List<T>::get(int pos) {
	int i = 0;
	if (abs(pos) + 1 > size) {
		std::cout << "element [" << pos << "] not found" << std::endl;
		std::cout << "press ENTER to finish . . .";
		std::cin.get();
		exit(1);
		//return 404;
	}

	if (pos < 0) pos = size - abs(pos);
	Node<T> * temp = head;
	while (i < pos) {
		temp = temp->next;
		i++;
	}
	return temp->data;
}

template <class T>
T& List<T>::operator[](int pos) {
	int i = 0;
	if (size == 0) {
		Node<T> * nd = new Node<T>(NULL);
		head = nd;
		tail = nd;
		return nd->data;
	}
	if (abs(pos) >= size) {
		std::cout << "element [" << pos << "] not found" << std::endl;
		std::cout << "press ENTER to finish . . .";
		std::cin.get();
		exit(2);
		//return 404;
	}

	if (pos < 0) pos = size - abs(pos);
	Node<T> * temp = head;
	while (i < pos) {
		temp = temp->next;
		i++;
	}
	return temp->data;
}

template <class T>
void List<T>::set(int pos, T data) {
	int i = 0;
	if (abs(pos) + 1 > size) {
		if (pos > 0) { this->push_back(data); }
		else { this->push_begin(data); }
		return;
	}
	if (pos < 0) pos = size - abs(pos);
	Node<T> * temp = head;
	while (i < pos) {
		temp = temp->next;
		i++;
	}
	temp->data = data;
}

template <class T>
void List<T>::insert(int pos, T data) {
	int i = 0;
	if (abs(pos) + 1 > size) {
		if (pos > 0) { this->push_back(data); }
		else { this->push_begin(data); }
		return;
	}
	if (pos < 0) { pos = size - abs(pos); }
	if (pos == 0) { this->push_begin(data); return; }
	if (pos == size - 1) { this->push_back(data); return; }
	Node<T> * temp = head;
	while (i < pos) {
		temp = temp->next;
		i++;
	}
	Node<T> * nd = new Node<T>(data, NULL, NULL);
	nd->next = temp;
	nd->prev = temp->prev;
	temp->prev->next = nd;
	temp->prev = nd;
}

template <class T>
void List<T>::remove(int pos) {
	int i = 0;
	if (abs(pos) + 1 > size) {
		std::cout << "element [" << pos << "] not found" << std::endl;
		std::cout << "press ENTER to finish . . .";
		std::cin.get();
		exit(3);
		//return 404;
	}
	if (pos == 0) {
		Node<T> * temp = head;
		head = head->next;
		head->prev = NULL;
		delete temp;
		return;
	}
	if (pos == size - 1) {
		Node<T> * temp = tail;
		tail = tail->prev;
		tail->next = NULL;
		delete temp;
		return;
	}

	Node<T> * temp = head;
	while (i < pos) {
		temp = temp->next;
		i++;
	}
	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;
	delete temp;
}

template <class T>
int List<T>::length() {
	return size;
}

#endif // !LIST_CPP