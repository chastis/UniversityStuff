#include <iostream>
#include <conio.h>

using namespace std;

template <typename T>
//функция которая обновляет кучу
void heapify(T *a, int i, int n) {
	int bigger, left, right;
	//текущий элемент
	bigger = i;
	//его левое дитя
	left = 2 * i + 1;
	//его правое дитя
	right = 2 * i + 2;
	//проверяем меньше ли наш элемент левого дитя
	if (left < n && a[bigger] < a[left]) {
		bigger = left;
	}
	//правого
	if (right < n && a[bigger] < a[right]) {
		bigger = right;
	}
	//если что то не так меняем их местами и запускаем рекурсию еще раз
	if (i != bigger) {
		swap(a[i], a[bigger]);
		heapify(a, bigger, n);
	}
	for (i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	i = 0;
}

template <typename T>
void buildHeap(T *a, int n) {
	//начинаем строить кучу с середины
	//так как i=n/2-1 будет иметь детей n-1 и n, что нам и требуется
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(a, i, n);
	}
}

template <typename T>
void heapSort(T *a, int n) {
	buildHeap(a, n);
	//проходим по масиву
	//который уже является кучей
	for (int i = n - 1; i > 0; i--) {
		//меняем первый и последний элемент подмассива
		swap(a[0], a[i]);
		//перестраиваем кучу
		heapify(a, 0, i);
	}
}

int main() {
	int i, *a, n;
	cin >> n;
	a = new int[n];
	for (i = 0; i < n; i++) {
		cin >> a[i];
	}

	heapSort(a, n);

	for (i = 0; i < n; i++) {
		cout << a[i] << " ";
	}

	cout << endl << "That's all Folks!" << endl;
	_getch();
	return 0;
}
