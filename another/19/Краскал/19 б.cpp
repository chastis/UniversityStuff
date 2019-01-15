#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

struct Edge {
	int a, b, w;
};

const int MAXN = 20000, MAXM = 100000;

int n, m, index[MAXM], component[MAXN],
	curComponent, kComponent[MAXN], cicle = 0;
vector <int> g[MAXN];
Edge e[MAXM];
vector <bool> used(MAXN, false);

int compare(const void* i, const void* j) {
    return (e[*(int*)i].w - e[*(int*)j].w);
}

void dfs(int v){
	used[v] = true;
	component[v] = curComponent;
	for (int i = 0; i < g[v].size(); i++) {
		int next = g[v][i];
		if (!used[next]) {
			dfs(next);
		}
	}
	used[v] = false;
}

int kraskal() {
    int minWeight = 0, pos = 0, change, notChange;
    while (pos < m) {
    	int curE = index[pos];
    	int compA = component[e[curE].a], compB = component[e[curE].b];
		if (compA != compB) {
			if (kComponent[compA] < kComponent[compB]) {
				change = e[curE].a;
				notChange = e[curE].b;
				kComponent[compB] += kComponent[compA];
				kComponent[compA] = 0;
			} else {
			    change = e[curE].b;
			    notChange = e[curE].a;
			    kComponent[compA] += kComponent[compB];
				kComponent[compB] = 0;
			}
			curComponent = component[notChange];
			dfs(change);
			g[notChange].push_back(change);
			g[change].push_back(notChange);
			minWeight += e[curE].w;
		} else {
		    cicle++;
		} 
		pos++;
    }
    return minWeight;
}


int main() {
    int a, b, w;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        e[i].a = --a;
        e[i].b = --b;
        e[i].w = w;
    }
    for (int i = 0; i < m; i++) {
    	index[i] = i;
	}
    qsort(index, m, sizeof(int), compare);
    for (int i = 0; i < n; i++) {
        component[i] = i;
    }
    for (int i = 0; i < n; i++) {
        kComponent[i] = 1;
    }
    cout << kraskal() << endl;
}

