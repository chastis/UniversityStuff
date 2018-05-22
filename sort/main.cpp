#include "Point3D.h"
#include "MyFunc.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <time.h>

using namespace std;
typedef unsigned int UINT;

int main() {
	
	ifstream fin("in.txt");
	int n;
	fin >> n;
	vector<Point3D> a(n), temp(n);
	for (int i = 0; i < n; i++) {
		fin >> a[i].x >> a[i].y >> a[i].z;
		temp[i].x = a[i].x; temp[i].y = a[i].y; temp[i].z = a[i].z;
	}
	int time = clock();

	cout << "INPUT" << endl;

	print(temp);

	cout << endl << "SORT BY ODD EVEN" << endl;
	
	time = clock();
	Odd_Even_Sort(temp);
	cout << "TIME : " << clock() - time << endl;
	print(temp);
	copy_array(a, temp);
	time = clock();

	cout << endl << "MERGE SORT" << endl;

	time = clock();
	Merge_Sort(temp);
	cout << "TIME : " << clock() - time << endl;
	print(temp);
	copy_array(a, temp);
	time = clock();

	cout << endl << "COMBINATION SORT" << endl;

	time = clock();
	Combination_sort(temp);
	cout << "TIME : " << clock() - time << endl;
	print(temp);
	copy_array(a, temp);
	time = clock();

	cout << endl << "MY FAVORITE SORT" << endl;

	time = clock();
	sort(temp.begin(), temp.end(),compare);
	cout << "TIME : " << clock() - time << endl;
	print(temp);
	time = clock();


	fin.close();
	
	cout << endl << "That's all Folks!" << endl;
	_getch();
	return 0;
}