#ifndef MYGRAF_H
#define MYGRAF_H
#include "MySet.h"
#include <iostream>

using namespace std;
int last_key_graf = 0;

class MyGraf
{
public:
	MySet data;
	vector<MyGraf * > children;

	MyGraf(MySet a) {
		data = a;
		last_key_graf++;
		key = last_key_graf;
	}
	MyGraf() {
		last_key_graf++;
		key = last_key_graf;
	}
	void insert(MySet a) {
		bool bl = true;
		MyGraf * new_child = new MyGraf(a);
		while (bl) {
			MyGraf * temp = this;
			for (int i = 0; i < temp->children.size(); i++) {
				if (temp->children[i]->data.intersection(a) || a.intersection(temp->children[i]->data)) { temp->children.push_back(new_child);  temp = temp->children[i]; break; }
			}
			bl = false;
			temp->children.push_back(new_child);
		}
	}
	void draw() {
		go_draw(this);
	}
private:
	int key;
	void go_draw(MyGraf *  branch) {
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

