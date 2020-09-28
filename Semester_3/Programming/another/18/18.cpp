#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 1000, MAXM = 10000;

bool incidenceMatrix[MAXN][MAXM], foundPath;
vector <int> g[MAXN], s[MAXN];
int n, m, st, fn, p[MAXN];
vector <bool> used(MAXN, false);
vector < vector <int> > fundamentalCycles;
set < pair <int, int> > usedE;

void readGraph() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> incidenceMatrix[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		vector <int> e;
		for (int j = 0; j < n; j++) {
			if (incidenceMatrix[j][i]) {
				e.push_back(j);
			}
		}
		g[e[0]].push_back(e[1]);
		g[e[1]].push_back(e[0]);
	}
}

void findSpanningTree(int cur) {
	used[cur] = true;
	for (int i = 0; i < g[cur].size(); i++) {
		int next = g[cur][i];
		if (!used[next]) {
			s[cur].push_back(next);
			s[next].push_back(cur);
			findSpanningTree(next);
		}
	}
}

void findPath(int cur) {
	if (foundPath) {
		return;
	}
	used[cur] = true;
	if (cur == fn) {
		foundPath = true;
		vector <int> cycle;
		cycle.push_back(fn);
		int v = fn;
		while (p[v] != -1) {
			v = p[v];
			cycle.push_back(v);
		}
		cycle.push_back(fn);
		fundamentalCycles.push_back(cycle);
	} else {
		for (int i = 0; i < s[cur].size(); i++) {
			int next = s[cur][i];
			if (!used[next]) {
				p[next] = cur;
				findPath(next);
			}
		}
	}
}

void printGraph() {
	cout << "Graph: " << endl;
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (auto v : g[i]) {
			cout << v << " ";
		}
		cout << endl;
	}
}

void printTree() {
	cout << "Spanning tree:" << endl;
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (auto v : s[i]) {
			cout << v <<  " ";
		}
		cout << endl;
	}
}

int main() {
	readGraph();	
	printGraph();
	findSpanningTree(0);
	printTree();
	for (int u = 0; u < n; u++) {
		for (auto v : g[u]) {
			bool foundE = false;
			for (auto w : s[u]) {
				if (w == v) {
					foundE = true;
					break;
				}
			}
			if (!foundE && usedE.find(make_pair(v, u)) == usedE.end()) {
				st = u;
				fn = v;
				for (int i = 0; i < n; i++) {
					used[i] = false;
				}
				p[st] = -1;
				foundPath = false;
				findPath(st);
				usedE.insert(make_pair(u, v));
			}
		}
	}
	cout << "Fundamental cycles:" << endl;
	for (auto c : fundamentalCycles) {
		for (auto v : c) {
			cout << v << " ";
		}
		cout << endl;
	}
}
