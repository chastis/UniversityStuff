#include "MySet.h"
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
using namespace std;

void MySet::draw() {
	cout << "SET {" << endl;
	cout << setprecision(2) << fixed << "(" << x << "," << y << ";" << z << "); r = " << r << ";" << endl;
	cout << "}" << endl;
}

void MySet::init() {
	x = (double)(rand() % 20001) / 1024 - 10;
	y = (double)(rand() % 20001) / 1024 - 10;
	z = (double)(rand() % 20001) / 1024 - 10;
	r = (double)(rand() % 3401) / 1024 + 1.6;

}

template <class T>
T sqr(T a) {
	return a*a;
}

bool MySet::include(MySet & a) {
	if (sqrt(sqr(x - a.x) + sqr(y - a.y) + sqr(z - a.z)) <= r - a.r) return true;
	return false;
}

bool MySet::intersection(MySet & a) {
	if (sqrt(sqr(x - a.x) + sqr(y - a.y) + sqr(z - a.z)) <= r + a.r) return true;
	return false;
}