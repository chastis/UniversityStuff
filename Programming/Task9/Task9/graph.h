#include <vector>
#include <fstream>
#include <iostream>
#include <stack>
using namespace std;

class graph {
	vector<vector<bool>> adjMatrix;
	int vNum, eNum;

	vector<int> vPow;
	vector<int> initialMark;

	void rewindPowers();
	int findSinglePower(int source);
	void collapse(int vertex, int to);
	int findSourceVertex();

public:
	graph(const string &input_name);
	~graph();

	void permute();

	void printMatrix();
	void printPowers();

};