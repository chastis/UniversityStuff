#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <ctime>
#include <ratio>

using namespace std;
using namespace std::chrono;

const int ARR_SIZE = 22500, PARTITIONS = 8,
	PARTS[PARTITIONS] = {1, 2, 10, 50, 150, 225, 2250, 22500},
	ARR_COUNT = 1;
	
int arr[ARR_SIZE], arrCopy[ARR_SIZE];

double oneThreadDurations[PARTITIONS], 
	multiThreadDurations[PARTITIONS];

int findMin(int n, int* a) {
	int minEl = a[0];
	for (int i = 1; i < n; i++) {
		minEl = min(minEl, a[i]);
	}
	return minEl;
}

int findMax(int n, int* a) {
	int maxEl = a[0];
	for (int i = 1; i < n; i++) {
		maxEl = max(maxEl, a[i]);
	}
	return maxEl;
}

void bubbleSort(int n, int* a) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = n - 1; j > i; j--) {
			if (a[j] < a[j - 1]) {
				swap(a[j], a[j - 1]);
			}
		}
	}
}

void bucketSort(int n, int* a, int p, bool isMulti) {
	if (n == 0) {
		return;
	}
	int minVal = findMin(n, a);
	int maxVal = findMax(n, a);
	int l = maxVal - minVal + 1;
	if (l == 1) {
		return;
	}
	vector <int> buckets[p];
	for (int i = 0; i < n; i++) {
		int bi = (a[i] - minVal) * p / l;
		buckets[bi].push_back(a[i]);
	}
	thread* sortThreads[p];
	int *arrBuckets[p], sizes[p];
	for (int i = 0; i < p; i++) {
		sizes[i] = buckets[i].size();
		arrBuckets[i] = new int[sizes[i]];
		for (int j = 0; j < sizes[i]; j++) {
			arrBuckets[i][j] = buckets[i][j];
		}
		if (isMulti) {
			sortThreads[i] = new thread(bubbleSort, sizes[i], arrBuckets[i]);
		} else {
			bubbleSort(sizes[i], arrBuckets[i]);
		}	
	}
	for (int i = 0; i < p; i++) {
		if (isMulti) {
			sortThreads[i]->join();
		}
		for (int j = 0; j < sizes[i]; j++) {
			buckets[i][j] = arrBuckets[i][j];
		}
		delete [] arrBuckets[i];
	}
	for (int i = 0, j = 0; i < n; j++) {
		for (auto num : buckets[j]) {
			a[i++] = num;
		}
	}
}

void simpleTest() {
	int n;
	cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	bucketSort(n, a, n / 2, true);
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void generateArr() {
	for (int i = 0; i < ARR_SIZE; i++) {
		arr[i] = rand() - RAND_MAX / 2;
	}
}

void copyArr() {
	for (int i = 0; i < ARR_SIZE; i++) {
		arrCopy[i] = arr[i];
	}
}

void timeTest() {
	for (int i = 0; i < PARTITIONS; i++) {
		oneThreadDurations[i] = multiThreadDurations[i] = 0;
	}
	for (int i = 0; i < ARR_COUNT; i++) {
		generateArr();
		for (int j = 0; j < PARTITIONS; j++) {
			duration<double> dur[2];
			for (int k = 0; k < 2; k++) {
				copyArr();
				high_resolution_clock::time_point t1 = high_resolution_clock::now();
				bucketSort(ARR_SIZE, arrCopy, PARTS[j], k);
		  		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		  		dur[k] = duration_cast<duration<double>>(t2 - t1);
			}
			oneThreadDurations[j] += dur[0].count();
			multiThreadDurations[j] += dur[1].count();
		}
	}
	for (int i = 0; i < ARR_COUNT; i++) {
		oneThreadDurations[i] /= ARR_COUNT;
		multiThreadDurations[i] /= ARR_COUNT;
	}
	cout << endl;
	cout << "Time test:" << endl;
	cout << "Arrays size = " << ARR_SIZE << endl;
	cout << "One thread time - Multithread time (in seconds)" << endl;
	for (int i = 0; i < PARTITIONS; i++) {
		cout << "Parts count = " << PARTS[i] << endl;
		cout << oneThreadDurations[i] << " - " << multiThreadDurations[i] << endl;
	}
}

int main() {
	srand(time(NULL));
	simpleTest();
	timeTest();
}
