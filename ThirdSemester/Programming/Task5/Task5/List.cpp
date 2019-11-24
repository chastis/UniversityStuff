#include "List.h"

using std::cout;
using std::endl;

Node::Node(int newData)
{
	data = newData;
	next = NULL;
}

Node::Node()
{

}



List::List()
{
	head = NULL;
}


List::~List()
{

}


void List::insert(int newData, int index)
{
	if (index < 0) {
		cout << "Invalid index";
		return;
	}
	Node* curr = new Node(newData);
	Node* tmp = head;
	int i = 1;

	if (!head) {
		head = curr;
	}
	else if (index == 1) {
		curr->next = tmp;
		head = curr;
	}
	else {
		while (i<index) {
			if (!tmp->next) {
				cout << "The end of the list was reached, the new node was added at the end" << endl;
				break;
			}
			tmp = tmp->next;
			i++;
		}
		curr->next = tmp->next;
		tmp->next = curr;
	}
}

void List::push_back(int newData) {
	Node* curr = new Node(newData);
	Node* tmp = head;

	if (!head) {
		head = curr;
	}
	else {
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = curr;
	}
}

void List::deleteExact(int index) {
	Node* curr = head;
	int i = 1;
	while (i < index - 1) {
		if (curr->next)
			curr = curr->next;
		else {
			cout << "Error: the node with index " << index << " does not exist in the list" << endl;
			return;
		}
		i++;
	}

	if (!curr->next) {
		cout << "Error: the node with index " << index << " does not exist in the list" << endl;
		return;
	}

	Node* tmp = curr->next;

	if (index == 1) {
		head = tmp;
		delete curr;
		return;
	}

	if (!curr->next->next) {
		curr->next = NULL;
	}
	else
		curr->next = curr->next->next;
	delete tmp;
}

void List::changeLink(int data)
{
	Node* curr = new Node(data);
	if (!head) {
		head = curr;
	}
	else {
		curr->next = head;
		head = curr;
	}
}

int List::pop()
{
	Node* tmp;
	tmp = head;

	if (!tmp) {
		cout << "\nError: Node is empty";
		return NULL;
	}

	if (!tmp->next) {
		head = NULL;
		return tmp->data;
	}

	head = head->next;
	return tmp->data;
}

void List::deleteList()
{
	if (!head) {
		cout << "List is empty" << endl;
		return;
	}

	while (head->next)
	{
		Node* tmp = head;
		head = head->next;
		delete tmp;
	}

	delete head;
	head = NULL;
}

void List::printList()
{
	if (!head)
	{
		cout << "Error: List is empty" << endl;
		return;
	}
	Node* curr = head;
	cout << "List: ";
	while (curr) {
		cout << curr->data << " ";
		curr = curr->next;
	}

	cout << endl;

}

int List::getData()
{
	return head->data;
}

Node* List::getPointer()
{
	return head;
}

void List::split(List* mainList, List* list1, List* list2, int N) {
	while (mainList->head) {
		if (mainList->head->data < N)
			list1->changeLink(pop());
		else
			list2->changeLink(pop());
	}
}

