#include <iostream>
#include <conio.h>

using namespace std;

//http://e-maxx.ru/algo/diofant_2_equation
//http://e-maxx.ru/algo/extended_euclid_algorithm

int gcd(int a, int b, int & x, int & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = gcd(b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

bool find_any_solution(int a, int b, int c, int & x0, int & y0, int & g) {
	g = gcd(abs(a), abs(b), x0, y0);
	if (c % g != 0)
		return false;
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0)   x0 *= -1;
	if (b < 0)   y0 *= -1;
	return true;
}

int main()
{
	cout << "Enter a, b, c" << endl;
	int a, b, c;
	int g, x0, y0;
	cin >> a;
	cin >> b;
	cin >> c;
	g = gcd(abs(a), abs(b), x0, y0);
	if (c % g != 0) {
		cout << "No solutions" << endl;
		_getch();
		return 1;
	}
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0)   x0 *= -1;
	if (b < 0)   y0 *= -1;
	cout << "Solution " << x0 << "+k*" << b / g << "    k e Z" << endl;
	cout << "         " << y0 << "+k*" << a / g << "    k e Z" << endl;
	cout << "That's all Folks!";
	_getch();
	return 0;
}

