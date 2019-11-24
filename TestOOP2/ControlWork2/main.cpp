#include "MySet.h"
#include "MyTree.h"
#include "MyGraf.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <fstream>
using namespace std;
int main() {
	ofstream fout("out.txt");

	srand(time(0));
	int n = 110;
	//cin << n;
	vector<MySet> a(n);
	for (int i = 0; i < n; i++) {
		a[i].init();
	}
	cout << "INPUT" << endl;
	for (auto now : a) {
		now.draw();
	}

	n = 0;
	int intersection = 0, includes = 0;
	for (int i = 0; i < a.size(); i++) {
		for (int j = i + 1; j < a.size(); j++) {
			if (a[i].include(a[j]) || a[j].include(a[i])) includes++;
			if (a[i].intersection(a[j])) intersection++;
		}
		n += a.size() - i - 1;
	}
	fout << "INTERSECTIONS " << (double)intersection / n << "% (" << intersection << " from " << n << ")" << endl;
	fout << "INCLUDES " << (double)includes / a.size() << "% (" << includes << " from " << a.size() << ")" << endl;

	MyTree<MySet> b;
	for (int i = 0; i < a.size(); i++) {
		b.insert(a[i]);
	}

	cout << "MYTREE//////////////////////////////////////////" << endl;
	b.draw();

	MyTree<MyGraf> c;
	cout << "TREE WITH GRAFS |||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	bool bl = true; int temp_deep = 0;
	while (bl) {
		MyGraf temp;
		for (int i = 0; i < a.size(); i++) {
			if (b[i].deep == temp_deep) temp.insert(b[i].data);
		}
		if (temp.children.size() == 0) {
			bl = false;
		}
		else {
			c.insert(temp);
		}
		temp_deep++;
	}
	c.draw();


	fout.close();
	cout << endl << "That's all Folks!" << endl;
	_getch();
	return 0;
}