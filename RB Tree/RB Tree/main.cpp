#include "rb_tree.h"
#include <iostream>
int main()
{
	RB_Tree tree;
	Pair one, two;
	one.key = "hello";
	one.value = "privet";
	two.key = "bye";
	two.value = "poka";
	tree.add(one);
	tree.add(two);

	tree.print();

	std::cin.get();
	return 0;
}