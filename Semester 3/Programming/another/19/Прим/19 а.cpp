#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100, INF = 10000000;

int n;
vector <int> included, g[MAXN], w[MAXN];
vector <bool> used(MAXN, false);

int prim() {
	used[0] = true;
    included.push_back(0);
	int minSpanning = 0;
	for (int i = 1; i < n; i++) {
		int minWeight = INF, minTop;
		for (int j = 0; j < included.size(); j++) {
			int cur = included[j];
			for (int k = 0; k < g[cur].size(); k++) {
				int next = g[cur][k];
				if (!used[next] &&
					w[cur][k] < minWeight) {
					minWeight = w[cur][k];
					minTop = next;
				}
			}
		}
		minSpanning += minWeight;
		used[minTop] = true;
		included.push_back(minTop);
	}
	return minSpanning;
}

int main(){
    int m, a, b, c;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b >> c;
        a--;
        b--;
        g[a].push_back(b);
        w[a].push_back(c);
        g[b].push_back(a);
        w[b].push_back(c);
    }
    
    cout << prim() << endl;
}
