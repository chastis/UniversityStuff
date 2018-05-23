#ifndef MYTREE_H
#define MYTREE_H
#include "MySet.h"
#include <iostream>

using namespace std;

int last_key = 0;

class MyTree
{
public:
	MySet data;
	vector<MyTree * > children;
	
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
		while (bl) {
			MyTree * temp = this;
			for (int i = 0; i < temp->children.size(); i++) {
				if (temp->children[i]->data.include(a)) { temp = temp->children[i]; break; }
			}
			bl = false;
			MyTree * new_child = new MyTree(a);
			temp->children.push_back(new_child);
		}
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


#endif // !MYSET_H

