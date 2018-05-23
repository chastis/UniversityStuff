#ifndef MYTREE_H
#define MYTREE_H
#include "MySet.h"
#include <iostream>

using namespace std;

int last_key = 0;

template <class T>
class MyTree
{
public:
	T data;
	vector<MyTree<T> * > children;
	
	MyTree(T a) {
		data = a;
		last_key++;
		key = last_key;
	}
	MyTree() {
		last_key++;
		key = last_key;
	}
	
	void insert(T a) {
		MyTree * new_child = new MyTree(a);
		this->children.push_back(new_child);
	}
	void draw() {
		go_draw(this);
	}
private:
	int key;
	void go_draw(MyTree *  branch) {
		cout << "NODE ::::: " << branch->key << endl;
		branch->data.draw();
		cout << "CHILDREN : ";
		if (branch->children.size() == 0) cout << "NONE" << endl; else cout << endl;
		for (int i = 0; i < branch->children.size(); i++) {
			branch->children[i]->data.draw();
		}
		for (int i = 0; i < branch->children.size(); i++) {
			go_draw(branch->children[i]);
		}
		
	}
};

template <>
class MyTree<MySet>
{
public:
	MySet data;
	vector<MyTree<MySet> * > children;
	int deep;

	MyTree(MySet a) {
		data = a;
		last_key++;
		key = last_key;
	}
	MyTree() {
		last_key++;
		key = last_key;
	}
	void insert(MySet a) {
		bool bl = true;
		int temp_deep = 1;
		while (bl) {
			MyTree * temp = this;
			for (int i = 0; i < temp->children.size(); i++) {
				if (temp->children[i]->data.include(a)) { temp = temp->children[i]; temp_deep++; break; }
			}
			bl = false;
			MyTree * new_child = new MyTree(a);
			new_child->deep = temp_deep;
			temp->children.push_back(new_child);
		}
	}
	void draw() {
		go_draw(this);
	}
	MyTree& go(int & j, MyTree *  branch){
		if (j == 0) return *branch;
		j--;
		MyTree temp;
		for (int i = 0; i < branch->children.size(); i++) {
			temp = go(j, branch->children[i]);
			if (j == 0) return temp;
		}
		return temp;
	}
	MyTree& operator[](int i) {
		return go(i, this);
	}
private:
	int key;
	void go_draw(MyTree *  branch) {
		cout << "NODE ::::: " << branch->key << endl;
		branch->data.draw();
		cout << "CHILDREN : ";
		if (branch->children.size() == 0) cout << "NONE" << endl; else cout << endl;
		for (int i = 0; i < branch->children.size(); i++) {
			branch->children[i]->data.draw();
		}
		for (int i = 0; i < branch->children.size(); i++) {
			go_draw(branch->children[i]);
		}

	}
};

#endif // !MYSET_H

