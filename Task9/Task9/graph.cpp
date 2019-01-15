#include "graph.h"

// Constructors
graph::graph(const string &input_name) {

	ifstream in(input_name);

	in >> vNum >> eNum;

	adjMatrix.assign(vNum, vector<bool>(vNum, false));
	vPow.assign(vNum, 0);
	initialMark.assign(vNum, 0);
	for (int i = 0; i < vNum; initialMark.at(i++) = i);

	int beg, end;
	for (int i = 0; i < eNum; i++) {
		in >> beg >> end;

		adjMatrix.at(beg).at(end) = true;	// Save edge
		vPow.at(end)++;						// Increase end power
	}
}
graph::~graph() {
	adjMatrix.~vector();
	vPow.~vector();
}

// Vertex power management
void graph::rewindPowers() {

	vPow.assign(vNum, 0);

	for (int i = 0; i < vNum; i++) {
		for (int j = 0; j < vNum; j++) {
			if (adjMatrix.at(i).at(j))
				vPow.at(j)++;
		}
	}
}
int graph::findSinglePower(int source) {
	for (int i = 0; i < vNum; i++)
		if (vPow.at(i) == 1 && i != source) return i;
	return -1;
}
// Collapse vertex into another
void graph::collapse(int vertex, int to) {
	stack<int> vStack;

	// Get all neighbour vertexes
	for (int i = 0; i < vNum; i++) {
		if (adjMatrix.at(vertex).at(i))
			vStack.push(i);
	}

	while (!vStack.empty()) {
		// If edge already exists, decrease edge number
		if (adjMatrix.at(to).at(vStack.top())) {
			eNum--;
		}
		// Create edge
		else {
			adjMatrix.at(to).at(vStack.top()) = true;
		}
		vStack.pop();
	}

	// Get iterator on row to delete
	auto delRow = adjMatrix.begin() + vertex;
	adjMatrix.erase(delRow);

	for (auto i = adjMatrix.begin(); i != adjMatrix.end(); i++) {
		auto delCol = i->begin() + vertex;
		i->erase(delCol);
	}

	vNum--; eNum--;
	rewindPowers();
}

// Use dfs to find vertex from which
// everything else is reachable
int graph::findSourceVertex() {
	vector<bool> visited(vNum, false);

	for (int i = 0; i < vNum; i++) {
		if (visited.at(i)) continue;
		vector<int> colors(vNum, 0);
		stack<int> vStack;

		vStack.push(i);
		while (!vStack.empty()) {
			int cur_v = vStack.top(); vStack.pop();

			colors.at(cur_v) = 1;
			visited.at(cur_v) = true;
			for (int j = 0; j < vNum; j++) {
				if (adjMatrix.at(cur_v).at(j) && !colors.at(j)) {
					vStack.push(j);
				}
			}
		}
		// If any vertex is not reachable, try next one
		bool flag = true;
		for (int j = 0; j < vNum; j++) {
			if (!colors.at(j)) {
				flag = false; break;
			}
		}
		if (flag) return i;
	}
	return -1;
}

void graph::permute() {
	// Get source
	int source = findSourceVertex();

	if (source == -1) {
		cout << "Impossible" << endl;
		return;
	}

	// While there are stil more than one vertex
	while (vNum > 1) {

		// Select vertex with power = 1
		int vertex_to_collapse = findSinglePower(source);

		// If no such vertex, than task is not possible
		if (vertex_to_collapse == -1) {
			cout << "Impossible!" << endl;
			return;
		}

		// Get parent
		int parent_vertex;
		for (int i = 0; i < vNum; i++) {
			if (adjMatrix.at(i).at(vertex_to_collapse)) {
				parent_vertex = i;
				break;
			}
		}

		// Collapse vertex into parent
		collapse(vertex_to_collapse, parent_vertex);
		// Change value for source, because of deleting row&column
		if (vertex_to_collapse < source)
			source--;
	}
	if (source == 0) {
		cout << "Permutations successful" << endl;
	}
	else cout << "FAIL U MAD BRO" << endl;
}

// Print adjacency matrix
void graph::printMatrix() {
	for (int i = 0; i < vNum; i++) {
		for (int j = 0; j < vNum; j++) {
			cout << adjMatrix.at(i).at(j) << " ";
		}
		cout << endl;
	}
}
// Print vertex powers
void graph::printPowers() {
	for (int i = 0; i < vNum; i++)
		cout << vPow.at(i) << " ";
	cout << endl;
}