#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

class Graph {
private:
	int numVertex;
	int numEdges;
	struct Edge {
		//begin's vertex
		int from;
		//end's vertex
		int to;
		Edge() {
			from = -1;
			to = -1;
		}
	};
	void pushEdge(int currentEdge, int currentVertex);
	int getVertex(int currentEdge, int currentVertex);
	void deleteSameEdge(int currentEdge, int currentVertex);

	//array with edges
	Edge *edgeArray;

	//for each vertex is its array with edges
	//incList[0] reurn us array with edges for 0th vertex
	vector<vector<int>> incList;
	// stack of vertexes 
	stack<int> st;
	//answer
	vector<int> resArray;
public:
	Graph();
	Graph(ifstream& input);
	~Graph();

	void findEulerCycle();
	void printResult();
};

#endif // !GRAPH_H