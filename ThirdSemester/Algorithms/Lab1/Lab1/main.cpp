#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <conio.h>

#define A "FileA.txt"
#define B "FileB.txt"
#define C "FileC.txt"
#define D "FileD.txt"
#define Data "DataFile.txt"

using namespace std;

void merge(vector<int> &arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	vector<int> L(n1), R(n2);

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(vector<int> &arr, int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

vector<int> read(string file, int s, int &pos)
{
	vector<int> v;
	int buff;
	ifstream fin(file);
	fin.seekg(pos);
	for (int i = 0; i < s; i++)
	{
		if (!fin.eof())
		{
			fin >> buff;
			v.push_back(buff);
		}
	}
	pos = fin.tellg();
	fin.close();
	return v;
}

int read(string file, int &pos)
{
	int buff;
	ifstream fin(file);
	fin.seekg(pos);
	if (!fin.eof())	fin >> buff;
	pos = fin.tellg();
	fin.close();
	return buff;
}

void write(string file, vector<int> v)
{
	ofstream fout(file, ios_base::app);
	for (int i = 0; i < v.size(); i++)
		fout << v[i] << " ";
	fout.close();
}

void write(string file, int i)
{
	ofstream fout(file, ios_base::app);
	fout << i << " ";
	fout.close();
}

void clear(string file)
{
	ofstream fout(file, ios_base::trunc);
	fout.close();
}

void clearAll()
{
	clear(A);
	clear(B);
	clear(C);
	clear(D);
}

bool empty(string file)
{
	ifstream fin(file);
	fin.seekg(0, ios::end);
	int p = fin.tellg();
	if (p == 0) return 1;
	else return 0;
}

void divide(string in, int size)
{
	int count = 0;
	string out = A;
	int pos = 0;
	vector<int> v;
	while (pos >= 0)
	{
		v = read(in, size, pos);
		mergeSort(v, 0, v.size() - 1);
		write(out, v);
		out = (out == A) ? B : A;
	}
}

void polyphaseMerge(int s)
{
	clearAll();
	string in1 = A, in2 = B, out = C;
	int pos1 = 0, pos2 = 0, ctr1, ctr2;
	int size = s;
	divide(Data, size);
	int c1, c2;
	while (!empty(in2))
	{
		if (out == C)
		{
			clear(C);
			clear(D);
		}
		else
		{
			clear(A);
			clear(B);
		}
		while (pos1 >= 0 || pos2 >= 0)
		{
			ctr1 = 0;
			ctr2 = 0;

			c1 = read(in1, pos1);
			if (pos1 < 0) c2 = 2147483647;

			c2 = read(in2, pos2);
			if (pos2 < 0) c2 = 2147483647;

			if ((pos1 < 0) && (pos2 < 0)) break;

			for (int i = 0; i < size * 2; i++)
			{
				if ((c1 < c2) && (pos1 >= 0))
				{
					ctr1++;
					write(out, c1);
					if (ctr1 >= size) c1 = 2147483647;
					else c1 = read(in1, pos1);
					if (pos1 < 0) c2 = 2147483647;
				}
				else if (pos2 >= 0)
				{
					ctr2++;
					write(out, c2);
					if (ctr2 >= size) c2 = 2147483647;
					else c2 = read(in2, pos2);
					if (pos2 < 0) c2 = 2147483647;
				}
			}
			if (out == A) out = B;
			else if (out == B) out = A;
			else if (out == C) out = D;
			else if (out == D) out = C;
		}
		size *= 2;

		if (in1 == A)
		{
			pos1 = 0;
			pos2 = 0;
			in1 = C;
			in2 = D;
			out = A;
		}
		else
		{
			pos1 = 0;
			pos2 = 0;
			in1 = A;
			in2 = B;
			out = C;
		}
	}
	clear(Data);
	ifstream fin((out == A) ? C : A);
	for (fin >> s; !fin.eof(); fin >> s)
		write(Data, s);
	clearAll();
}

int main()
{
	int size;
	cout << "Enter size of memory: ";
	cin >> size;
	polyphaseMerge(size);

	cout << "That's all Folks!" << endl;
	_getch();
	return 0;
}

