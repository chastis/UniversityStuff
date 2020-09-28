#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const int MAXN = 20;

int n, m;
vector <int> g[MAXN], ng[MAXN], used;
vector < pair < vector <int>, pair <int, int> > > hammocks;
bool use[MAXN];

bool check(int s, int t) {
	for (int i = 0; i < used.size(); i++) {
		if (i != t) {
			for (int j = 0; j < g[used[i]].size(); j++) {
				if (!use[g[used[i]][j]]) {
					return false;
				}
			}
		}
	}
	for (int i = 0; i < used.size(); i++) {
		if (i != s) {
			for (int j = 0; j < ng[used[i]].size(); j++) {
				if (!use[ng[used[i]][j]]) {
					return false;
				}
			}
		}
	}
	return true;
}

void generate(int pos) {
	if (pos == n) {
		used.clear();
		for (int i = 0; i < n; i++) {
			if (use[i]) {
				used.push_back(i);
			}
		}
		if (used.size() < 2 || used.size() == n) {
			return;
		}
		for (int i = 0; i < used.size(); i++) {
			for (int j = i + 1; j < used.size(); j++) {
				if (check(i, j)) {
					auto h = make_pair(used, make_pair(i, j));
					hammocks.push_back(h);
				} 
			}
		}
		return;
	}
	use[pos] = true;
	generate(pos + 1);
	use[pos] = false;
	generate(pos + 1);
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		ng[v].push_back(u);
	}
	generate(0);
	for (auto h : hammocks) {
		cout << "in = " << h.second.first << "  out = " << h.second.second << endl;
		for (int i = 0; i < h.first.size(); i++) {
			cout << h.first[i] << " ";
		}
		cout << endl;
	}
}
