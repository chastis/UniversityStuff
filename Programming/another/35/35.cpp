#include <iostream>
#include <vector>

using namespace std;

enum Color {
	WHITE, GRAY, BLACK
};

const int MAXN = 10000;

int n, m;
vector <int> g[MAXN];
vector <int> t(MAXN, - 1);
vector <Color> c(MAXN, WHITE);

int dfs(int cur) {
	if (c[cur] == GRAY) {
		cout << "No" << endl;
		exit(0);
	}
	c[cur] = GRAY;
	int maxT = 0;
	for (int i = 0; i < g[cur].size(); i++) {
		int next = g[cur][i];
		if (c[next] == BLACK) {
			maxT = max(maxT, t[next] + 1);
		} else {
			maxT = max(maxT, dfs(next) + 1);
		}
	}
	t[cur] = maxT;
	c[cur] = BLACK;
	return maxT;
}

void topologicalSort() {
	for (int i = 0; i < n; i++) {
		dfs(i);
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
	}
	topologicalSort();
 	int longestPath = 0;
	for (int i = 0; i < n; i++) {
		longestPath = max(longestPath, t[i]);
	}
	if (longestPath == n - 1) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
}
