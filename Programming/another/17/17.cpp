#include <iostream>
#include <vector>

using namespace std;

void dfs_straight(int, bool*, vector <int>&, vector <int>*);
void dfs_reverse(int, bool*, vector <int>&, vector <int>*);

int main()
{
	int n, m;
	cin >> n >> m;
	vector <int> *g = new vector <int>[n];
	vector <int> *gr = new vector <int>[n];
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		gr[v].push_back(u);
	}
	
	bool *used = new bool[n];
	for (int i = 0; i < n; i++)
	{
		used[i] = false;
	}
	vector <int> order;
	for (int i = 0; i < n; i++)
	{
		if (!used[i])
		{
			dfs_straight(i, used, order, g);
		}
	}
	vector <int> cur_component;
	vector <int> *components = new vector <int>[n];
	int num_of_comp = 0;
	for (int i = 0; i < n; i++)
	{
		used[i] = false;
	}
	for (int i = n - 1; i >= 0; i--)
	{
		int cur = order[i];
		if (!used[cur])
		{
			cur_component.clear();
			dfs_reverse(cur, used, cur_component, gr);
			components[num_of_comp++] = cur_component;
		}
	}
	int *belong = new int[n];
	for (int i = 0; i < num_of_comp; i++)
	{
		for (int j = 0; j < components[i].size(); j++)
		{
			belong[components[i][j]] = i + 1;
		}
	}
	
        cout << num_of_comp << endl;
	for (int i = 0; i < n; i++)
	{
		cout << belong[i] << ' ';
	}
	cout << endl;
}

void dfs_straight(int cur, bool *used, vector <int> &order, vector <int> *g)
{
	used[cur] = true;
	for (int i = 0; i < g[cur].size(); i++)
	{
		int next = g[cur][i];
		if (!used[next])
		{
			dfs_straight(next, used, order, g);
		}
	}
	order.push_back(cur);
}
void dfs_reverse(int cur, bool *used, vector <int> &component, vector <int> *gr)
{
	used[cur] = true;
	component.push_back(cur);
	for (int i = 0; i < gr[cur].size(); i++)
	{
		int next = gr[cur][i];
		if (!used[next])
		{
			dfs_reverse(next, used, component, gr);
		}
	}
}
