#ifndef MYFUNC_H
#define MYFUNC_H

#include "Point3D.h"
#include <vector>

typedef enum{more, less, equal} sign;

using namespace std;

template<class T>
sign comp(T  a, T  b);


bool compare(Point3D &a, Point3D &b);


void Odd_Even_Sort(vector<Point3D> & a);

void Merge_Sort(vector<Point3D> & a, int left, int right);

void Combination_sort(vector<Point3D> & a);

//in B copy from A
template <class T>
void copy_array(vector<T> & a, vector<T> & b);

template <class T> 
void print(T &a);

#include "MyFunc.inc"
#endif  