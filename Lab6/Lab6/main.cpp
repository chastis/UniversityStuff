#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

const int P = 31;
const int MAXN = 100000;

int power[MAXN];
int ha[MAXN], hb[MAXN];
string a, b;

void calculatePowers(int n) {
	power[0] = 1;
	for (int i = 1; i < n; i++) {
		power[i] = power[i - 1] * P;
	}
}

void makeHash(string s, int* h) {
	h[0] = s[0];
	for (int i = 1; i < s.size(); i++) {
		power[i] = power[i - 1] * P;
		h[i] = h[i - 1] + s[i] * power[i];
	}
}

bool trivialCheck(int l, int r) {
	for (int i = l; i <= r; i++) {
		if (a[i] != b[i - l]) {
			return false;
		}
	}
	return true;
}

int main() {
	cin >> a;
	cin >> b;
	if (a.size() != b.size()) {
		cout << "NO" << endl;
		cout << "That's all Folks!" << endl;
		_getch();
		return 1;
	}
	int n = a.size();
	a += a;
	calculatePowers(2 * n);
	makeHash(a, ha);
	makeHash(b, hb);
	for (int l = 0; l < n - 1; l++) {
		int r = l + n - 1;
		if (ha[r] - (l ? ha[l - 1] : 0) == hb[n - 1] * power[l] &&
			trivialCheck(l, r)) {
			cout << "YES" << endl;
			cout << "That's all Folks!" << endl;
			_getch();
			return 0;
		}
	}
	cout << "NO" << endl;
	cout << "That's all Folks!" << endl;
	_getch();
	return 1;
}
