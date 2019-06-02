#include "Sortings.h"
#include "helpers.h"

using std::swap;

Sortings::Sortings()
{

}

Sortings::~Sortings()
{

}

std::function<void(std::vector<Element>::iterator , std::vector<Element>::iterator , std::function<bool(Element, Element)>)> Sortings::getBubbleSort()
{

	auto func = [](std::vector<Element>::iterator begin, std::vector<Element>::iterator end, std::function<bool(Element,Element)> comp)
	{
		for (auto i = begin; i != end; i++)
		{
			for (auto j = i; j != end; j++)
			{
				if (comp(*i, *j))
				{
					swap(*i, *j);
				}
			}
		}
	};

	return func;
}
/*
void Sorting::start_sort(QString name_algorithms, const int *arr, int size)
{
	int *array = new int[static_cast<unsigned long long>(size)];
	for (int i = 0; i < size; i++)
		array[i] = arr[i];
	if (name_algorithms == "Bubble sort")
	{
		BubbleSort(array, size);
	}
	else if (name_algorithms == "Bogosort")
	{
		BogoSort(array, size);
	}
	else if (name_algorithms == "Selection sort")
	{
		SelectionSort(array, size);
	}
	else if (name_algorithms == "Insertion sort")
	{
		InsertionSort(array, size);
	}
}

void Sorting::BubbleSort(int *numbers, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		bool was_swap = 0;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (numbers[j] > numbers[j + 1])
			{
				emit nextIteration(j, j + 1, 1);
				swap(numbers[j], numbers[j + 1]);
				was_swap = 1;
			}
			else
			{
				emit nextIteration(j, j + 1, 0);
			}
		}
		if (!was_swap)
		{
			break;
		}
	}
	emit nextIteration(-1, -1, 0);
}

void Sorting::BogoSort(int *arr, int size)
{
	while (!isSorted(arr, size))
	{
		arr = shuffle(arr, size);
		emit nextIteration(arr);
	}
}

bool Sorting::isSorted(int *arr, int size)
{
	for (int i = 1; i < size; i++)
		if (arr[i] < arr[i - 1]) return false;
	return true;
}

int *Sorting::shuffle(int *arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		int rand = QRandomGenerator::global()->bounded(0, size);
		swap(arr[i], arr[rand]);
	}
	return arr;
}

void Sorting::SelectionSort(int *arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int min_pos = i;
		for (int j = i + 1; j < size; j++)
		{
			emit nextIteration(j, min_pos, 0);
			if (arr[j] < arr[min_pos])
			{
				min_pos = j;
			}
		}
		if (min_pos > i)
		{
			emit nextIteration(i, min_pos, 1);
			swap(arr[i], arr[min_pos]);
		}
	}
	emit nextIteration(-1, -1, 0);
}

void Sorting::InsertionSort(int *arr, int size)
{
	for (int i = 1; i < size; i++)
	{
		int cur = arr[i];
		int j = i - 1;
		while (j >= 0)
		{
			if (arr[j] <= cur) break;
			arr[j + 1] = arr[j];
			emit nextIteration(j, j + 1, 1);
			j--;
		}
		arr[j + 1] = cur;
	}
	emit nextIteration(-1, -1, 0);
}

*/