#include <iostream>
#include <cmath>
#include <conio.h>

using namespace std;

int main() {
	double x, temp_x, e;
	cin >> x >> e;
	temp_x = x;
	const double PI_MATH = atan(1) * 4;
	int minus_pi_4 = 0;
	while (temp_x - PI_MATH / 4 > 0) {
		temp_x -= PI_MATH / 4;
		minus_pi_4++;
	}
	minus_pi_4 /= 4;
	double sum = 1, temp = 42;
	int i = 1, fact = 1;
	while (true) {
		fact *= 2 * i * (2 * i - 1);
		double current_temp = (i % 2 == 0) ? pow(temp_x, 2 * i) / fact : -pow(temp_x, 2 * i) / fact;
		if (abs(temp) - abs(current_temp) < e) break;
		temp = current_temp;
		sum += temp;
		i++;
	}
	cout << "in Teylor Series : " <<sum << endl;
	cout << "cos(x) = " << cos(x) << endl;
	cout << "error in calculations = " << abs(cos(x) - sum) << endl;
	cout << "That's all Folks!" << endl;
	_getch();
	return 0;
}