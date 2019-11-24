#define _USE_MATH_DEFINES
//https://works.doklad.ru/view/qYgaul2bTZI.html
//https://www.calc.ru/Resheniye-Sistem-Lineynykh-Uravneniy-Metod-Vrashcheniya.html
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <math.h>
double a;
double b;
const int n = 5;
double *X = new double[n + 1];
double eps = 0.001;

using namespace std;
double functionF(double x) { return sin(x); }
double functionU(double x) { return sin(x); }
double functionK(double x, double s) { return 1; }



int main() {
	setlocale(LC_ALL, ".ACP");
	a = 0;
	b = 2 * (M_PI);
	double h = (b - a) / (n - 1);
	double *f = new double[n];
	double **K = new double*[n];
	double **hi = new double*[n];

	for (int i = 0; i<n; i++)
		K[i] = new double[n]; //а это сама матрица коэффициентов
	for (int i = 0; i<n; i++)
		hi[i] = new double[n]; //матрица вращения: на главной диагонали единицы, остальные элементы нули, на
							   //нужные места ставим cos, sin, -sin, cos


	for (int i = 0; i<n; i++) {
		X[i] = a + h*i;
	}

	for (int i = 0; i<n; i++)
		f[i] = functionF(X[i]); //правая часть

	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++) {
			if (i == j)
				K[i][j] = 1 + h*functionK(X[i], X[j]); //U(x_1) с единичным коэф-том входит только в первое уравнение. 
			else                                  //во всех остальных уравнениях у него нулевой коэф-т. 
				K[i][j] = h*functionK(X[i], X[j]);
		}  //а у элементов на диагонали коэф-т = 1+K(x_i, x_j); что-то я не понимаю, верно ли у меня тут записано,
		   //что первый столбец, кроме первого элемента, должен быть нулевым?

	cout << "\n";

	cout << "\n";
	for (int i = 0; i<n; i++)
		printf("f[%d]=%.3f ", i, f[i]);
	int p = 1;

	while (p<5) { //пробное условие для теста


		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				if (i == j)
					hi[i][j] = 1;
				else hi[i][j] = 0;
			}

		for (int i = 0; i<n; i++) {
			for (int j = 0; j<n; j++) {
				double fi = atan(K[i][j] / (K[i][j] * K[i][j] + K[j][j] * K[j][j]));
				double cosfi = cos(fi), sinfi = sin(fi);
				hi[i][j] = cosfi;
				hi[j][j] = cosfi;
				hi[i][j] = -sinfi;
				hi[j][i] = sinfi;

				f[i] = f[i] * cosfi + f[j] * sinfi;

				K[i][i] = cosfi*K[i][i] + sinfi*K[i][j];
				K[j][j] = -sinfi*K[j][i] + cosfi*K[j][j];
				K[i][j] = cosfi*K[j][i] + sinfi*K[j][j];
			}
		}


		printf("\nСледующее приближение:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) { printf("K[%d][%d]=%.2f  ", i, j, K[i][j]); }cout << "\n";
		}; p++;
	}

	cout << "\n";
	system("pause");
	return 0;
}