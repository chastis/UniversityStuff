#ifndef FIGURES_H
#define FIGURES_H
#include <cmath>
#include <limits>

bool double_is_equal(const double &a,const double &b) {
	return abs(a - b) < std::numeric_limits<double>::epsilon();
}

class Point
{
public:
	Point(double x = 0, double y = 0) {
		this->x = x;
		this->y = y;
	}
	~Point() {};
	double get_x() {
		return x;
	}
	double get_y() {
		return y;
	}
	void set(double x, double y) {
		this->x = x;
		this->y = y;
	}
	void set_x(double x) {
		this->x = x;
	}
	void set_y(double y) {
		this->y = y;
	}
	double distance_to_point(Point a) {
		return sqrt((a.get_x() - x)*(a.get_x() - x) + (a.get_y() - y)*(a.get_y() - y));
	}
private:
	double x;
	double y;
};

class Line
{
public:
	Line() {
		first.set(0, 0);
		second.set(0, 0);
	}
	Line(double x1, double y1, double x2 = 0, double y2 = 0) {
		first.set(x1, y1);
		second.set(x2, y2);
	}
	void set(double x1, double y1, double x2 = 0, double y2 = 0) {
		first.set(x1, y1);
		second.set(x2, y2);
	}
	void set_first(double x1, double y1) {
		first.set(x1, y1);
	}
	void set_second(double x2, double y2) {
		second.set(x2, y2);
	}
	Point get_first() {
		return first;
	}
	Point get_second() {
		return second;
	}
	//AX+BY+C=0
	double get_A() {
		return (second.get_y() - first.get_y());
	}
	//AX+BY+C=0
	double get_B() {
		return (first.get_x() - second.get_x());
	}
	//AX+BY+C=0
	double get_C() {
		return (this->get_A * -first.get_x() + this->get_B * first.get_y());
	}
	~Line() {}
	double length() {
		return first.distance_to_point(second);
	}
	double distance_to_point(Point a) {
		double temp = sqrt(this->get_A()*this->get_A() + this->get_B()*this->get_B());
		temp = abs(this->get_A()*a.get_x() + this->get_B()*a.get_y() + this->get_C) / temp;
		return temp;
	}
	bool is_parallel(Line a) {
		return (double_is_equal(get_A() / a.get_A(), get_B() / a.get_B()) && !double_is_equal(get_A() / a.get_A(), get_C() / a.get_C()));
	}
	bool is_equal(Line a) {
		return (double_is_equal(get_A() / a.get_A(), get_B() / a.get_B()) && double_is_equal(get_A() / a.get_A(), get_C() / a.get_C()));
	}
private:
	Point first;
	Point second;
};

class Parallelogram
{
public:
	Parallelogram() {
		first.set(0, 0);
		second.set(0, 0);
	}
	Line get_first() {
		return first;
	}
	Line get_second() {
		return second;
	}
	void set_fisrt(Line first) {
		this->first = first;
	}
	void set_second(Line second) {
		this->second = second;
	}
	void set(Line first, Line second) {
		set_fisrt(first);
		set_second(second);
	}
	double perimeter() {
		return (first.length() * 2 + 2 * first.get_first().distance_to_point(second.get_first));
	}
	double square() {
		return (first.length()*second.distance_to_point(first.get_first()));
	}

	~Parallelogram() {}


private:
	Line first;
	Line second;
};

#endif // !FIGURES_H
