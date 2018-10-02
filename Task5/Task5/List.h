#ifndef LIST_H
#define LIST_H

#include <iostream>

class Node
{
	friend class List;
private:
	Node();
	Node(int newData);
	Node* next;
	int data;

};

class List
{
public:
	List();
	~List();

	void insert(int newData, int index);
	void push_back(int newData);
	void deleteExact(int index);
	void deleteList();
	void printList();
	int getData();
	int pop();
	void changeLink(int data);
	void split(List* mainList, List* list1, List* list2, int N);

private:
	Node* getPointer();
	Node* head;
};

#endif // !LIST_H