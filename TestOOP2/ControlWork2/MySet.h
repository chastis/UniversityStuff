#ifndef MYSET_H
#define MYSET_H
#include <vector>
using namespace std;

class MySet
{
public:
	// center on x
	double x;
	//center on y
	double y;
	//center on z
	double z;
	//radius
	double r;
	void draw();
	void init();
	bool include(MySet & a);
	bool intersection(MySet & a);
private:

};


#endif // !MYSET_H

