#include <iostream>
#include <omp.h>
#include <conio.h>
#include <intrin.h>
#include <iomanip>
#include <chrono>
#include <stdlib.h>
#include <ctime>
#include <math.h>

using namespace std;
const int N = 2000;

void init(int *A) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			A[i * N + j] = rand() % 5;
}

int main() {
	srand(time(NULL));
	int i, j, k;

	int *A = new int[N*N];
	int *B = new int[N*N];
	int *C = new int[N*N];
	init(A);
	init(B);
	clock_t begin_time = clock();
#pragma omp parallel for private(j,k)
	for (i = 0; i < N; i++)
		for (k = 0; k < N; k++) {
			int sum = 0;
			for (j = 0; j < N; j++)
				sum += A[i * N + j] * B[j * N + k];
			C[i * N + k] = sum;
		}
	std::cout << "N = " << N << "; time = " << int(clock() - begin_time) << "\n";

	delete[] A;
	delete[] B;
	delete[] C;

	system("pause");
	return 0;
}