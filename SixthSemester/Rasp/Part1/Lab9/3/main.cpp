#include <tbb/parallel_for.h>
#include "tbb/blocked_range2d.h"
#include "tbb/tick_count.h"
#include <chrono>
#include <iostream>
using namespace tbb;

const int N = 2000;
int a[N][N];
int b[N][N];
int c[N][N];

class Multiply {
public:
	void operator()(blocked_range2d<int> r) const {
		for (size_t i = r.rows().begin(); i != r.rows().end(); ++i) {
			for (size_t j = r.cols().begin(); j != r.cols().end(); ++j) {
				int sum = 0;
				for (int k = 0; k < N; ++k) {
					sum += a[i][k] * b[k][j];
					c[i][j] = sum;
				}
			}
		}
	}
};

int main() {
	srand(time(NULL));
	int duration;
	tick_count startTime;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			a[i][j] = rand() % 5;
			b[i][j] = rand() % 5;
			c[i][j] = 0;
		}
	}

	startTime = tick_count::now();
	parallel_for(blocked_range2d<int>(0, N, 16, 0, N, 32), Multiply());
	duration = (tick_count::now() - startTime).seconds() * 1000;

	std::cout << "N = " << N << "; " << duration << " ms";
	return 0;
}