#include "graph.h"
#include <conio.h>

int main() {
	graph myGraph("data.in");
	myGraph.printMatrix();
	myGraph.permute();

	std::cout << "That's all Folks!" << std::endl;
	_getch();
	return 0;
};