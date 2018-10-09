#include <iostream>
#include <conio.h>
#include "Graph.h"

using namespace std;

int main() {
	ifstream fin("graph.txt");
	Graph graph(fin);
	graph.findEulerCycle();
	graph.printResult();
	fin.close();
	cout << "That's all Folks!";
	_getch();
}