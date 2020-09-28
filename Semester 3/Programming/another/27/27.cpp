#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100000;

int n, m, mn[MAXN], tn[MAXN];
vector <int> g[MAXN];
vector <bool> used(MAXN, false);

int dfs(int cur, int num) {
	used[cur] = true;
	mn[cur] = num;
	num++;
	for (int i = 0; i < g[cur].size(); i++) {
		int next = g[cur][i];
		if (!used[next]) {
			num = dfs(next, num);
		}
	}
	return num;
}	

void bfs(int st, int num) {
	for (int i = 0; i < n; i++) {
		used[i] = false;
	}
	vector <int> v[2];
	v[0].push_back(st);
	used[st] = true;
	for (int d = 0; d < n; d++) {
		int vi = d % 2;
		for (int i = 0; i < v[vi].size(); i++) {
			int cur = v[vi][i];
			tn[cur] = num++;
			for (int j = 0; j < g[cur].size(); j++) {
				int next = g[cur][j];
				if (!used[next]) {
					used[next] = true;
					v[!vi].push_back(next);
				}
			}
		}
		v[vi].clear();
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(0, 0);
	bfs(0, 0);
	cout << "M-numeration: ";
	for (int i = 0; i < n; i++) {
		cout << mn[i] << " ";
	}
	cout << endl;
	cout << "T-numeration: ";
	for (int i = 0; i < n; i++) {
		cout << tn[i] << " ";
	}
	cout << endl;
}
