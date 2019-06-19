#include <iostream>
#include <string>
#include "RB_Tree.h"

using namespace std;

int main()
{
	RB_Tree<string> tree;
	string one, two, three;
	one = "hello";
	two = "bye";
	tree.add(one);
	tree.add(two);
	three = "one";
	tree.add(three);
	tree.print();


	cin.get();
	return 0;
}