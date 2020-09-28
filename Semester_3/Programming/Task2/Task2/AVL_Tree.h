#ifndef AVLTREE_DEMO_H
#define AVLTREE_DEMO_H

#include <iostream>

using namespace std;

template <typename KeyType, typename DataType>
class AVLTree {

	static const int DRAWING_SIDE = 100,
		MAX_DRAWING_SIZE = 15,
		MAX_KEY_AND_DATA_SIZE = 50,
		BORDER = 30;

	struct Node {
		KeyType key;
		DataType data;
		Node *left, *right, *prev;
		int height;
	};

	Node *root;
	int size;

	Node* findRec(Node *cur, KeyType key, bool exact);
	void leftRotate(Node *cur);
	void rightRotate(Node *cur);
	void balance(Node *cur);
	bool insertRec(Node *cur, KeyType key, DataType data);
	bool eraseRec(Node *cur, KeyType key);
	void printRec(Node *cur, bool asList);
	void fillTable(int& column, int depth, Node *cur, Node ***nodeTable);
	char* toCharPointer(string s, int n);

public:

	AVLTree();
	~AVLTree();
	bool insert(KeyType key, DataType data);
	bool erase(KeyType key);
	DataType* find(KeyType key);
	void print();
	void printAsList();
	void draw();
};

#include "AVL_Tree.cpp"

#endif // AVLTREE_DEMO_H
