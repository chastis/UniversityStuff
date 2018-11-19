#include <iostream>
#include <queue>
#include <vector>

using namespace std;



int main() {
	int n, m;
	cout << "Enter size: ";
	cin >> n;
	queue<int>q;
	vector<vector<int>> g(n);
	vector<int>used(n);
	vector<int>c(n, 0);
	for (int j = 0; j < n; j++) for (int i = 0; i < n; i++) g[j].push_back(0);
	for (int i = 0; i<n; i++) {
		for (int j = i + 1; j<n; j++) {
			cout << "A[" << i + 1 << "][" << j + 1 << "]: ";
			cin >> m;
			g[i][j] = m;
			g[j][i] = m;
		}
	}

	q.push(0);
	c[0] = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		used[v] = true;

		for (int i = 0; i<n; i++) {
			if (g[v][i]) {
				if (!used[i]) {
					c[i] = 1 - c[v];
					used[i] = true;
					q.push(i);
				}
				else {
					if (c[i] == c[v]) {
						cout << "IMPOSSIBLE\n";
						system("pause");
						return 0;
					}
				}
			}
		}
	}

	cout << "POSSIBLE\n";
	system("pause");
}