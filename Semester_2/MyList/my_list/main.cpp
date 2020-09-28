#include <iostream>
using namespace std;
#include "List.h"


int main() {
	List<int> a;
	a.set(1, 2);
	a.set(1, 3);
	a.set(42, 42);
	a.set(-42, -42);
	cout << a << endl;
	cout << a.get(0) << endl;
	cout << a.get(-1) << endl;
	//cout << a.get(42) << endl;
	a[1] = a[2];
	cout << a[1] << endl;
	//cout << a[42] << endl;
	cout << a << endl;
	a.insert(0, 0);
	a.insert(a.length() - 1, a.length() - 1);
	a.insert(1, 1);
	cout << a << endl;
	a.remove(1);
	a.remove(a.length() - 1);
	a.remove(0);
	cout << a << endl;
	cout << "That's all Folks!" << endl;
	cin.get();
	return 0;
}