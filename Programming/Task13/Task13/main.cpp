#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;

int** readFile(int& numRows, int& numColumns) {
	ifstream fin;
	fin.open("matrix.txt");
	fin >> numRows >> numColumns;

	int** matrix = new int*[numRows];
	for (int i = 0; i < numRows; i++)
		matrix[i] = new int[numColumns];

	for (int i(0); i < numRows; i++) {
		for (int j(0); j < numColumns; j++) {
			fin >> matrix[i][j];
		}
	}

	return matrix;
}

int main() {
	int numRows = 0;
	int numColumns = 0;
	int** matrix = readFile(numRows, numColumns);
	int currentSum = 0;
	int maxSum = 0;
	int x[2], y[2];

	for (int itrY = 0; itrY < numRows; itrY++) {
		for (int itrX = 0; itrX < numColumns; itrX++) {
			for (int diagonalItrY = itrY + 1; diagonalItrY < numRows; diagonalItrY++){
				for (int diagonalItrX = itrX + 1; diagonalItrX < numColumns; diagonalItrX++) {
					currentSum = matrix[itrY][itrX];
					currentSum += matrix[diagonalItrY][diagonalItrX];
					currentSum += matrix[itrY][diagonalItrX];
					currentSum += matrix[diagonalItrY][itrX];
					if (currentSum > maxSum) {
						x[0] = itrX;
						x[1] = diagonalItrX;
						y[0] = itrY;
						y[1] = diagonalItrY;
						maxSum = currentSum;
					}
					currentSum = 0;
				}
			}
		}
	}

	cout << "maxSum: " << maxSum << endl;
	cout << "(" << x[0] << ";" << y[0] << ")" << "  " << "(" << x[1] << ";" << y[0] << ")" << endl;
	cout << "(" << x[0] << ";" << y[1] << ")" << "  " << "(" << x[1] << ";" << y[1] << ")" << endl;
	cout << matrix[y[0]][x[0]] << "  " << matrix[y[1]][x[0]] << endl;
	cout << matrix[y[0]][x[1]] << "  " << matrix[y[1]][x[1]];
	_getch();
}