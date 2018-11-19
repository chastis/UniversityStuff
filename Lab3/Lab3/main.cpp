#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>

using namespace std;

const int MAXN = 1e5 + 1;

int n, d;
float h[MAXN];

void swap(float &a, float &b) {
	int c = a;
	a = b;
	b = c;
}

void heapify(int i) {
	int maxP = i;
	float maxV = h[i];
	for (int k = 1; k <= d; k++) {
		int p = d * i + k;
		if (p >= n) {
			break;
		}
		if (h[p] > maxV) {
			maxV = h[p];
			maxP = p;
		}
	}
	if (maxP != i) {
		swap(h[i], h[maxP]);
		heapify(maxP);
	}
}

void buildHeap() {
	for (int i = n - 1; i >= 0; i--) {
		heapify(i);
	}
}

float extractMax() {
	float maxV = h[0];
	swap(h[0], h[n - 1]);
	n--;
	heapify(0);
	return maxV;
}

void increaseKey(int i, float v) {
	if (i == 0) {
		h[0] = v;
		return;
	}
	int p = (i - 1) / d;
	if (h[p] < v) {
		h[i] = h[p];
		increaseKey(p, v);
	}
	else {
		h[i] = v;
	}
}

void insert(float v) {
	n++;
	increaseKey(n - 1, v);
}

void printHeap() {
	cout << "Heap: ";
	for (int i = 0; i < n; i++) {
		cout << h[i] << " ";
	}
	cout << endl;
}

int main() {
	ifstream cin("data.in");

	cin >> n >> d;
	if (d < 1) {
		cout << "Incorrect d" << endl;
		return 0;
	}
	for (int i = 0; i < n; i++) {
		cin >> h[i];
	}
	cout << "Start array: ";
	for (int i = 0; i < n; i++) {
		cout << h[i] << " ";
	}
	cout << endl;

	buildHeap();
	printHeap();

	string op;
	while (cin >> op) {
		if (op == "inc") {
			int i;
			float v;
			cin >> i >> v;
			increaseKey(i, v);
			cout << "Key in position " << i << " increased to " << v << endl;
		}
		else if (op == "ex") {
			cout << "Extracted max = " << extractMax() << endl;
		}
		else {
			float v;
			cin >> v;
			insert(v);
			cout << "Inserted element " << v << endl;
		}
		printHeap();
	}

	cout << "That's all Folks!" << endl;
	_getch();
	return 0;
}
