#include <conio.h>
#include <iostream>
#include <vector>
using namespace std;

// struct of coficients to build spline in every node of the graphics
struct Points
{
	double a, b, c, d, x;
};

class Spline 
{
private:
	vector<Points> points;
	int N; // number of nodes

public:
	Spline() {

	}
	~Spline() {

	}
	// function to build spline
	// x - nodes of the graphics, must be sorted in ascend order  //ascend = from low to high
	// y - values of the function in the nodes
	// N - number of nodes
	void build_spline(double *x, double *y, int N)
	{
		this->N = N;

		// initialization of the array of splines
		for (int i = 0; i < N; ++i)
		{
			Points temp;
			temp.x = x[i];
			temp.a = y[i];
			points.push_back(temp);
		}
		points[0].c = 0;

		// solving the Spline using coefficiens from c[i] for tridiagonal matrix
		// Tridiagonal matrix algorithm - forward going 
		//https://ru.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%BF%D1%80%D0%BE%D0%B3%D0%BE%D0%BD%D0%BA%D0%B8
		//where matrix are based on formula:
		//c[i-1]*h[i-1]+2*c[i]*(h[i]+h[i-1])+c[i+1]*h[i]=3*( (a[i+1]-a[i])/h[i] - (a[i]-a[i-1])/h[i-1] )
		//where c[0] = c[N-1] = 0
		//where h[i]=x[i] - x[i - 1]
		//where a[i] is y[i]

		//formuls for those coefficient we take from algoritm of spline from wiki
		//https://ru.wikipedia.org/wiki/%D0%9A%D1%83%D0%B1%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B9_%D1%81%D0%BF%D0%BB%D0%B0%D0%B9%D0%BD

		double *alpha = new double[N - 1];
		double *beta = new double[N - 1];
		double A, B, C, F, hI, hI2, z;
		alpha[0] = beta[0] = 0;

		for (int i = 1; i < N - 1; ++i)
		{
			hI = x[i] - x[i - 1];
			hI2 = x[i + 1] - x[i];
			//next formules look on Wikipedia
			A = hI;
			C = 2 * (hI + hI2);
			B = hI2;
			F = 3 * ((y[i + 1] - y[i]) / hI2 - (y[i] - y[i - 1]) / hI);
			//z is znamenatel' in difficult formula
			z = (A * alpha[i - 1] + C);
			alpha[i] = -B / z;
			beta[i] = (F - A * beta[i - 1]) / z;
		}

		points[N - 1].c = (F - A * beta[N - 2]) / (C + A * alpha[N - 2]);

		// Finding the solution - backwards algorithm
		for (int i = N - 2; i > 0; --i)
			points[i].c = alpha[i] * points[i + 1].c + beta[i];

		delete[] beta;
		delete[] alpha;

		// using coefficients c[i] - searching b[i] and d[i]
		for (int i = N - 1; i > 0; --i)
		{
			hI = x[i] - x[i - 1];
			points[i].d = (points[i].c - points[i - 1].c) / (hI * 3);
			points[i].b = hI * (2 * points[i].c + points[i - 1].c) / 3 + (y[i] - y[i - 1]) / hI;
		}
	}

	// calculate values in every point of interpolated function
	double f(double x)
	{
		Points tempPoints;
		if (x <= points[0].x) // if x is less than the first element of the array use the first
			tempPoints = points[0];
		else if (x >= points[N - 1].x) // use last element if x is greater than last element
			tempPoints = points[N - 1];
		else // in other cases points is laying between the border values
		{
			int i = 0;
			int j = N - 1;
			//bin search
			while (i + 1 < j)
			{
				int k = i + (j - i) / 2;
				if (x <= points[k].x)
					j = k;
				else
					i = k;
			}
			tempPoints = points[j];
		}

		double dx = (x - tempPoints.x);
		return tempPoints.a + (tempPoints.b + (tempPoints.c + tempPoints.d * dx) * dx) * dx; // calculate value of spline in the specific point
	}
};

void main()
{
	Spline cubic_spline;
	//int N = 6;
	//double x[6] = { -0.5, 1.5, 2, 3.5, 6, 9 };
	//double y[6] = { 2.5, 6, -3.5, -7, -10, 2 };
	//double xi = 2.5;
	int N = 7;
	double x[7] = { -1.5, -1, -0.5, 0, 0.5, 1, 1.5 };
	double y[7] = { -0.7, 0, 0.7, 1, 0.7, 0, -0.7 };
	double xi = -1.3;
	//example solution from
	//http://www.mathros.net.ua/znahodzhennja-nablyzhenogo-znachennja-tablychno-zadanoi-funkcii-vykorystovujuchy-kubichnu-splajn-interpoljaciju.html
	//answer is -0.43
	cubic_spline.build_spline(x, y, N);
	cout << cubic_spline.f(xi) << endl;
	cout << "That's all Folks!";
	_getch();
}