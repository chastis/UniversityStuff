#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1001;

int ans[MAXN][MAXN];

bool win(int n, int p) {
	if (n == 1) {
		return false;
	}
	for (int i = 1; i <= min(p + 1, n - 1); i++) {
		int newN = n - i, newP = i;
		if (ans[newN][newP] == 0 || !win(n - i, i)) {
			return ans[n][p] = 1;
		} 
	}
	return ans[n][p] = 0;
}

int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ans[i][j] = -1;
		}
	}
	vector <int> wns;
	for (int i = 1; i <= min(k, n - 1); i++) {
		if (!win(n - i, i)) {
			wns.push_back(i);
		}
	}
	if (wns.empty()) {
		cout << "Player 1 cannot win" << endl;
	} else {
		cout << "Winning numbers: ";
		for (auto num : wns) {
			cout << num << " ";
		}
		cout << endl;
	}
}
