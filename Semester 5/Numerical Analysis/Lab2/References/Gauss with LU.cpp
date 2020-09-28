
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<iomanip>
using namespace std;
void inverse(float **matrix, float **result, int size)
{

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			result[i][j] = 0.0;

		result[i][i] = 1.0;
	}


	double **copy = new double *[size]();


	for (int i = 0; i < size; ++i)
	{
		copy[i] = new double[size];

		for (int j = 0; j < size; ++j)
			copy[i][j] = matrix[i][j];
	}

	for (int k = 0; k < size; ++k)
	{
		if (fabs(copy[k][k]) < 1e-8)
		{
			bool changed = false;

			for (int i = k + 1; i < size; ++i)
			{
				if (fabs(copy[i][k]) > 1e-8)
				{
					std::swap(copy[k], copy[i]);
					std::swap(result[k], result[i]);


					changed = true;

					break;
				}
			}

			if (!changed)
			{

				for (int i = 0; i < size; ++i)
					delete[] copy[i];

				delete[] copy;


			}
		}


		double div = copy[k][k];


		for (int j = 0; j < size; ++j)
		{
			copy[k][j] /= div;
			result[k][j] /= div;
		}


		for (int i = k + 1; i < size; ++i)
		{

			double multi = copy[i][k];


			for (int j = 0; j < size; ++j)
			{
				copy[i][j] -= multi * copy[k][j];
				result[i][j] -= multi * result[k][j];
			}
		}
	}


	for (int k = size - 1; k > 0; --k)
	{

		for (int i = k - 1; i + 1 > 0; --i)
		{

			double multi = copy[i][k];


			for (int j = 0; j < size; ++j)
			{
				copy[i][j] -= multi * copy[k][j];
				result[i][j] -= multi * result[k][j];
			}
		}
	}

	for (int i = 0; i < size; ++i)
		delete[] copy[i];

	delete[] copy;

	cout << "inverse matrix : " << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			cout << result[i][j] << "    ";
		cout << endl;
	}


}
int main()
{
	int e,i, j, n, m,  k,q,a,count=0;
	double max, temp,temp1;

	cout << "Number of equations: ";
	cin >> n;
	cout << "Number of variables: ";
	cin >> m;
	m += 1;
	float **matrix = new float *[n];
	for (i = 0; i<n; i++)
		matrix[i] = new float[m];

	matrix[0][0] = 8.30; matrix[0][1] = 3.22; matrix[0][2] = 4.10; matrix[0][3] = 1.90; matrix[0][4] = -10.05; matrix[1][0] = 3.92; matrix[1][1] = 8.45; matrix[1][2] = 7.18; matrix[1][3] = 2.46; matrix[1][4] = 12.21; matrix[2][0] = 3.77; matrix[2][1] = 6.61; matrix[2][2] = 8.04; matrix[2][3] = 2.28; matrix[2][4] =14.85; matrix[3][0] = 2.21; matrix[3][1] = 3.05; matrix[3][2] = 1.69; matrix[3][3] = 6.99; matrix[3][4] = -8.35;

	float **L = new float *[n];
	for (i = 0; i<n; i++)
		L[i] = new float[n];
	for (i = 0; i<n; i++)
	{
		for (j = 0; j < n; j++)
			L[i][j] = 0;
	}
	float **obe = new float *[n];
	for (i = 0; i<n; i++)
		obe[i] = new float[n];
	for (i = 0; i<n; i++)
	{
		for (j = 0; j < n; j++) {
			obe[i][j] = 0;
			obe[i][i] = 1;
		}
	}


	/*for (i = 0; i < n; i++)//введення матриці головної
	{

		for (j = 0; j < m; j++)
		{
			cout << " Element " << "[" << i + 1 << " , " << j + 1 << "]: ";

			cin >> matrix[i][j];

		}



	}*/




	cout << "matrix: " << endl;
	for (i = 0; i<n; i++)//виведення головної
	{
		for (j = 0; j<m; j++)
			cout << matrix[i][j] << " ";
		cout << endl;

	}


	inverse(matrix, obe, n);
	double norm1 = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			norm1 += matrix[i][j]*matrix[i][j];
		}
	}
	double norm2 = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			norm2 += obe[i][j] * obe[i][j];
		}
	}
	norm1 = sqrt(norm1);
	norm2 = sqrt(norm2);
	double *xx = new double[m];
	double *det = new double[n];
	for ( k = 0; k<n; k++) //прямий хід
	{
		max = abs(matrix[k][k]);
		i = k;
		for (m = k + 1; m<n; m++)
			if (abs(matrix[m][k])>max)
			{
				i = m;
				max = abs(matrix[m][k]);
			}

		if (max == 0)
		{
			cout << "error!" << endl;
		}

		if (i != k)
		{
			count++;
			for (j = k; j < n + 1; j++)
			{

				temp = matrix[k][j];
				matrix[k][j] = matrix[i][j];

				matrix[i][j] = temp;

			}
		}
		det[k] = matrix[k][k];
		for (int j = k; j <n; j++) {
				L[j][k] = matrix[j][k];

		}


		max = matrix[k][k];
		matrix[k][k] = 1;
		for (j = k + 1; j < n + 1; j++) {
			matrix[k][j] = matrix[k][j] / max;

		}

		for (i = k + 1; i < n; i++)
		{
			temp = matrix[i][k];
			matrix[i][k] = 0;
			if (temp != 0)
				for (j = k + 1; j < n + 1; j++) {
					matrix[i][j] = matrix[i][j] - temp * matrix[k][j];

				}

		}
		cout << "matrix: " << endl;
		for (i = 0; i<n; i++)//виведення головної
		{
			for (j = 0; j<m+1; j++)
				cout <<setw(10)<<fixed<<setprecision(6)<< matrix[i][j] << " ";
			cout << endl;

		}
	}
	cout << "U matrix: " << endl;
	for (int i = 0; i<n; i++)// У матриця
	{
		for (int j = 0; j<n; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	cout << " L matrix: " << endl;
	for (i = 0; i<n; i++)//виведення Lmatrix
	{
		for (j = 0; j<n; j++)
			cout << L[i][j] << " ";
		cout << endl;

	}
	double deter=1*pow(-1,count);
	for (i = 0; i < n; i++) {
		deter *= det[i];
	}
	cout << "determinant :" << deter << endl;

	double obymovl = norm1 * norm2;
	cout << "Chyslo obymovl :" << obymovl << endl;
	//зворотній хід
	xx[n - 1] = matrix[n - 1][n];
	for (i = n - 2; i >= 0; i--)
	{
		xx[i] = matrix[i][n];
		for (j = i + 1; j<n; j++) xx[i] -= matrix[i][j] * xx[j];
	}

	//виводимо розв*язки
	for (i = 0; i<n; i++)
		cout << xx[i] << " ";
	cout << endl;

	delete[] matrix;

	return 0;
}
