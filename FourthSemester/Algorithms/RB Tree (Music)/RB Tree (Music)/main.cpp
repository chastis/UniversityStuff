#include <iostream>
#include "music_shop.h"
#include "rb_tree.h"
using std::cout;
using std::cin;
using std::endl;

int main()
{
	Performer a, b, c, d;
	a.name = "2";
	b.name = "1";
	c.name = "3";
	d.name = "4";
	RB_Tree tree;
	tree.add(a);
	tree.add(b);
	tree.add(c);
	tree.add(d);
	tree.print();/*
	cout << "find something" << endl;
	tree.find("4"); tree.find("4");
	tree.print();*/
	int x;
	while (cin >> x) cout << tree.find_i(x).name << endl;
	cout << "That's all, Folks!" << endl;
	cin.get();
	return 0;
}
