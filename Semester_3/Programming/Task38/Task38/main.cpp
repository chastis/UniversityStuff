#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, const char * argv[]) {


	int g1[105][105];
	int g[105][105];

	int n;
	cin >> n;
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			cin >> g[i][j];
			g1[i][j] = g[i][j];
		}
	}

	int u, v;
	cin >> u >> v;


	vector< int >dist(n, 10000);
	vector< int >parent(n, -1);
	vector< int >used(n, false);
	queue< int >q;


	q.push(u);
	dist[u] = 0;
	parent[u] = u;
	while (!q.empty()) {
		int k = q.front();
		q.pop();
		used[k] = true;
		for (int i = 0; i<n; i++) {
			if (!used[i] && g[i][k]) {
				used[i] = true;
				q.push(i);
				parent[i] = k;
				dist[i] = dist[k] + 1;

			}
		}

	}

	cout << dist[v] << endl;


	while (true) {
		dist.assign(n, 10000);
		parent.assign(n, -1);
		used.assign(n, false);
		q.push(u);
		dist[u] = 0;
		parent[u] = u;
		while (!q.empty()) {
			int k = q.front();
			q.pop();
			used[k] = true;
			for (int i = 0; i<n; i++) {
				if (!used[i] && g[i][k]) {
					used[i] = true;
					q.push(i);
					parent[i] = k;
					dist[i] = dist[k] + 1;


				}
			}

		}
		if (!used[v]) {
			break;

		}
		int t = v;
		while (t != u) {
			g[t][parent[t]] = g[t][parent[t]] = 0;
			cout << t << ' ';
			t = parent[t];
		}
		cout << u << endl;
	}


	cout << "vertexes" << endl;

	while (true) {
		dist.assign(n, 10000);
		parent.assign(n, -1);
		used.assign(n, false);
		q.push(u);
		dist[u] = 0;
		parent[u] = u;
		while (!q.empty()) {
			int k = q.front();
			q.pop();
			used[k] = true;
			for (int i = 0; i<n; i++) {
				if (!used[i] && g1[i][k]) {
					used[i] = true;
					q.push(i);
					parent[i] = k;
					dist[i] = dist[k] + 1;


				}
			}

		}
		if (!used[v]) {
			return 0;

		}
		int t = v;
		while (t != u) {
			if (t != v) {
				for (int i = 0; i < n; i++) {
					g1[i][t] = g1[t][i] = 0;
				}
			}
			cout << t << ' ';
			t = parent[t];
		}
		cout << u << endl;
	}


}

