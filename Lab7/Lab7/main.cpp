#include <iostream>
#include <string>
#include <conio.h>

const int P = 31;
const int MAXM = 1000;

int m, n;
int power[MAXM];
int ha[MAXM][MAXM], hb[MAXM][MAXM];
std::string a[MAXM], b[MAXM];

void calculatePowers(int n) {
	power[0] = 1;
	for (int i = 1; i < n; i++) {
		power[i] = power[i - 1] * P;
	}
}

void makeHash(std::string s, int* h) {
	h[0] = s[0];
	for (int i = 1; i < s.size(); i++) {
		power[i] = power[i - 1] * P;
		h[i] = h[i - 1] + s[i] * power[i];
	}
}

bool trivialCheck(int t, int q, int l, int r) {
	for (int i = l; i <= r; i++) {
		if (a[q][i] != b[q - t][i - l]) {
			return false;
		}
	}
	return true;
}

bool check(int t, int q, int l, int r) {
	if (ha[q][r] - (l ? ha[q][l - 1] : 0) != hb[q - t][n - 1] * power[l]) {
		return false;
	}
	else if (trivialCheck(t, q, l, r)) {
		return true;
	}
	return false;
}

int main() {
	std::cout << "Enter the size of text (n) and size of substr (m)" << std::endl;
	std::cin >> m >> n;
	if (m < n) {
		std::cout << "NO" << std::endl;
		std::cout << "That's all Folks!" << std::endl;
		_getch();
		return 1;
	}
	calculatePowers(m);
	for (int i = 0; i < m; i++) {
		std::cin >> a[i];
		makeHash(a[i], ha[i]);
	}
	for (int i = 0; i < n; i++) {
		std::cin >> b[i];
		makeHash(b[i], hb[i]);
	}
	for (int i = 0; i < m - n + 1; i++) {
		for (int j = 0; j < m - n + 1; j++) {
			bool found = true;
			for (int k = i; k < i + n; k++) {
				if (!check(i, k, j, j + n - 1)) {
					//cout << k << " " << j  << " " << j + n - 1 << endl;
					found = false;
					break;
				}
			}
			if (found) {
				std::cout << "YES in [" << i << ", " << j << "]" << std::endl;
				std::cout << "That's all Folks!" << std::endl;
				_getch();
				return 0;
			}
		}
	}
	std::cout << "NO" << std::endl;
	std::cout << "That's all Folks!" << std::endl;
	_getch();
	return 1;
}
