#ifndef POINT3D_H
#define POINT3D_H
#include <iostream>
using namespace std;


class Point3D {
public:
	double x, y, z;
	void draw() {
		cout << x << " " << y << " " << z << endl;
	}
};

#endif  

