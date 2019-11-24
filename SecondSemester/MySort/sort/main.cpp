#include "Point3D.h"
#include "MyFunc.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <time.h>
#include <chrono>

using namespace std;
#define PRINT false

int main() {
	
	srand(time(0));
	ifstream fin("in.txt");
	int n;
	//fin >> n;
	cin >> n;
	vector<Point3D> a(n), temp(n);
	for (int i = 0; i < n; i++) {
		//fin >> a[i].x >> a[i].y >> a[i].z;
		a[i].x = rand(); a[i].y = rand(); a[i].z = rand();
		temp[i].x = a[i].x; temp[i].y = a[i].y; temp[i].z = a[i].z;
	}
	auto time = chrono::high_resolution_clock::now();

	cout << "INPUT" << endl;

	if (PRINT) print(temp);

	cout << endl << "SORT BY ODD EVEN" << endl;
	
	time = chrono::high_resolution_clock::now();
	Odd_Even_Sort(temp);
	cout << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << "ns" << endl;
	if (PRINT) print(temp);
	copy_array(a, temp);

	cout << endl << "MERGE SORT" << endl;

	time = chrono::high_resolution_clock::now();
	Merge_Sort(temp);
	cout << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << "ns" << endl;
	if (PRINT) print(temp);
	copy_array(a, temp);

	cout << endl << "COMBINATION SORT" << endl;

	time = chrono::high_resolution_clock::now();
	Combination_sort(temp);
	cout << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << "ns" << endl;
	if (PRINT) print(temp);
	copy_array(a, temp);

	cout << endl << "MY FAVORITE SORT" << endl;

	time = chrono::high_resolution_clock::now();
	sort(temp.begin(), temp.end(),compare);
	cout << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << "ns" << endl;
	if (PRINT) print(temp);


	fin.close();
	
	cout << endl << "That's all Folks!" << endl;
	_getch();
	return 0;
}