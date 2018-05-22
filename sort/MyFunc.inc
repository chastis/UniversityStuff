#ifndef MYFUNC_CPP
#define MYFUNC_CPP

#include "MyFunc.h"

using namespace std;

template<class T>
sign comp(T  a, T  b) {
	if (a > b) return sign::more;
	else if (a < b) return sign::less;
	else return sign::equal;
}

bool compare(Point3D &a, Point3D &b) { // a > b = true // true == sort is INcorrect
	switch (comp(a.x, b.x))
	{
	case sign::more:
		return true;
	case sign::less:
		return false;
	case sign::equal:
		switch (comp(a.y, b.y))
		{
		case sign::more:
			return true;
		case sign::less:
			return false;
		case sign::equal:
			switch (comp(a.z, b.z))
			{
			case sign::more:
				return true;
			case sign::less:
				return false;
			case sign::equal:
				return true;
			}
		}
	}
}

void Odd_Even_Sort(vector<Point3D> & a) {
	bool flag = true;
	do {
		for (int i = 0; i < a.size(); i++) {
			for (int j = (i % 2) ? 0 : 1; j < a.size() - 1; j += 2) {
				if (!compare(a[j], a[j + 1])) {
					swap(a[j], a[j + 1]);
					flag = false;
				}
			}
		}
	} while (flag);
}
void Merge_Sort_Rec(vector<Point3D> & a, Point3D * temp, int left = 0, int right = -1) {
	//stupid user
	if (right <= -1 || right >= a.size()) {
		right = a.size() - 1;
	}
	if (left < 0 || left >= a.size()) {
		left = 0;
	}
	//exit
	if (left == right) {
		return;
	}
	//rec
	Merge_Sort_Rec(a, temp, left, (right - left) / 2 + left); Merge_Sort_Rec(a, temp, (right - left) / 2 + 1 + left, right);

	//init
	int i_1 = left, i_2 = (right - left) / 2 + 1 + left; int i = left;
	//Point3D * temp = new Point3D[right - left + 1];
	for (int i = left; i <= right; i++) temp[i] = a[i];

	//main loop
	while (true) {
		if (i_1 > (right - left) / 2 + left && i_2 > (right - left) / 2 + 1 + left) break;
		if (i_1 <= (right - left) / 2 + left && compare(temp[i_1], temp[i_2])) {
			a[i] = temp[i_1];
			i++;
			i_1++;
		}
		else {
			a[i] = temp[i_2];
			i++;
			i_2++;
		}
	}
}

void Merge_Sort(vector<Point3D> & a, int left = 0, int right = -1) {
	Point3D * temp = new Point3D[a.size()];
	Merge_Sort_Rec(a, temp, left, right);
	delete[] temp;
}

template <class T>
void print(T &a) {
	for (auto now : a) {
		now.draw();
	}
}

void Combination_sort(vector<Point3D> & a) {
	// n^2  vs  n*log(n)
	if (a.size() >= 10) Merge_Sort(a); else Odd_Even_Sort(a);
}

//in B copy from A
template <class T>
void copy_array(vector<T> & a, vector<T> & b) {
	for (int i = 0; i < a.size(); i++) {
		b[i] = a[i];
	}
}

#endif  