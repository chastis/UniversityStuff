#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

#define INF 1e9

struct edge {
	int from;
	int to;
	int cost;
	edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
};

vector<int> Bellman_Ford(vector<edge> & gr, int v, int n, int m) {
	vector<int> d(n, INF);
	d[v] = 0;
	for (;;) {
		bool any = false;
		for (int j = 0; j<m; ++j)
			if (d[gr[j].from] < INF)
				if (d[gr[j].to] > d[gr[j].from] + gr[j].cost) {
					d[gr[j].to] = d[gr[j].from] + gr[j].cost;
					any = true;
				}
		if (!any)  break;
	}
	return d;

}



void Jonson_algo(vector<vector<pair<int, int> > > & gr_by_lists, vector<edge> gr_by_edge) {
	size_t s = gr_by_lists.size();
	size_t size = gr_by_lists.size();
	size_t edges_cnt = gr_by_edge.size();

	for (int i = 0; i < size; i++) {
		gr_by_edge.push_back(edge(s, i, 0));
	}

	vector<int> h = Bellman_Ford(gr_by_edge, s, size + 1, gr_by_edge.size());

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < gr_by_lists[i].size(); j++) {
			gr_by_lists[i][j].second += (h[i] - h[gr_by_lists[i][j].first]);
		}//counting new costs
	}


	//Djicstra algo
	vector<vector<int> > d(size, std::vector<int>(size, INF));

	for (s = 0; s < size; s++) {

		d[s][s] = 0;
		priority_queue < pair<int, int> > q;
		q.push(make_pair(0, s));

		while (!q.empty()) {
			int v = q.top().second, cur_d = -q.top().first;
			q.pop();

			if (cur_d > d[s][v])  continue;

			for (size_t j = 0; j<gr_by_lists[v].size(); ++j) {
				int to = gr_by_lists[v][j].first,
					len = gr_by_lists[v][j].second;
				if (d[s][v] + len < d[s][to]) {
					d[s][to] = d[s][v] + len;

					q.push(make_pair(-d[s][to], to));
				}
			}
		}
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i != j && d[i][j] != INF) {
				d[i][j] += (h[j] - h[i]);
			}
		}//back to costs
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << d[i][j] << " ";
		}
		cout << endl;
	}

	ofstream fout("gr_output.txt");
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (d[i][j] != INF)fout << i + 1 << "->" << j + 1 << " [ label = \"" << d[i][j] << "\" ]" << endl;
		}
	}

}

int main() {
	ifstream cin("input.txt");
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int, int> > >  gr_by_lists(n);
	vector<edge> gr_by_edge;

	vector<edge> gr_to_show;
	int from, to, cost;
	for (int i = 0; i < m; i++) {
		cin >> from >> to >> cost;
		from--; to--;
		gr_by_edge.push_back(edge(from, to, cost));
		gr_by_edge.push_back(edge(to, from, cost));
		gr_by_lists[from].push_back({ to, cost });
		gr_by_lists[to].push_back({ from, cost });

		gr_to_show.push_back(edge(to, from, cost));
	}

	ofstream fout("gr_input.txt");

	for (auto el : gr_to_show) {
		fout << el.from + 1 << "->" << el.to + 1 << " [ label = \"" << el.cost << "\" ]" << endl;
	}

	Jonson_algo(gr_by_lists, gr_by_edge);
	return 0;
}

