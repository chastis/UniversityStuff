#include "RB_Tree.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<memory.h>

using namespace std;

//! набор тестирующих процедур 
int main()
{
	RBTree tree;
	int n, i;
	bool array[SIZE];
	srand(time(0));
	memset(&tree.stat, 0, sizeof(tree.stat)); tree.stat.black_depth = -1;
	memset(array, false, sizeof(array));
	for (n = 0; n<SIZE * 100; n++) {
		printf("pass: %d of %d\r", n + 1, SIZE * 100);
		i = rand() % SIZE; array[i] = true;  tree.Insert(i);
		i = rand() % SIZE; array[i] = false; tree.Remove(i);
	}
	putchar('\n');
	switch (tree.Check()) {
	case ERROR_STRUCT:   printf("*** structure error\n\a"); break;
	case ERROR_BALANCE:  printf("*** balance error\n\a");   break;
	default:
		printf("insert - max turn count: %d\n", tree.stat.insert.max_count);
		printf("insert - average turn count: %g\n", (double)tree.stat.insert.sum_count / tree.stat.insert.sum_divider);
		printf("remove - max turn count: %d\n", tree.stat.remove.max_count);
		printf("remove - average turn count: %g\n", (double)tree.stat.remove.sum_count / tree.stat.remove.sum_divider);
		printf("nodes count: %d\n", tree.stat.nodes_count);
		printf("black depth: %d\n", tree.stat.black_depth);
		printf("max   depth: %d\n", tree.stat.max_depth);
		break;
	}
	if (tree.TreeWalk(array, SIZE)) printf("*** context error\n\a");
	tree.Clear();
	getchar();
	return 0;
}
