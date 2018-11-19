#include<iostream>
#include <conio.h>

using std::swap;
using std::cout;
using std::endl;

void segregate(int arr[], int n);

int main()
{
	int count_negative = 0;
	//negative and positive numbers like key 0 and 1
	int arr[] = { -12, 11, -13, -5, 6, -7, 5, -3, -6 };
	int n = sizeof(arr) / sizeof(arr[0]);
	segregate(arr, n);
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;

	cout << "That's all Folks!" << endl;
	_getch();
	return 0;
}

//Segregation of negative and positive numbers in an array without using extra space, and maintaining
//insertion order and in O(n) time complexity.
void segregate(int arr[], int n)
{
	int count_negative = 0;
	for (int i = 0; i < n; i++)
		if (arr[i] < 0)
			count_negative++;

	int i = 0, j = i + 1;
	while (i != count_negative)
	{

		// If number is negative, update
		// position of next positive number.
		if (arr[i] < 0) {
			i++;
			j = i + 1;
		}

		// If number is positive, move it to
		// index j and increment j.
		else if (arr[i] > 0 && j < n)
		{
			swap(arr[i], arr[j]);
			j++;
		}
	}
}
