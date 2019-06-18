#include <iostream>
#include "Tree.h"
#include "HistoryTree.h"
int main()
{
	RBTree<int> t1{ 2,1,3 };
	auto t2 = t1.Insert(4);
	auto t3 = t2.Insert(-1);
	auto t4 = t3.Insert(0);
	HistoryTree<int> pSet{ t1, t2};
	pSet.PrintForViz("test.out");
	system("pause");
	return 0;
}