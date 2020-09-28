#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <chrono>
#include "String_Searching_Algorithm.h"

using namespace std;

// http://algolist.manual.ru/search/esearch/
int main() {
	ifstream fin("data.in");
	//подстрока (мы ищем ее)
	string sub;
	//строка в которой мы ищем
	string s;
	getline(fin, sub);
	getline(fin, s);
	auto time = chrono::high_resolution_clock::now();

	//SIMPLE SEARCH
	cout << "Simple Search" << endl;
	time = chrono::high_resolution_clock::now();
	cout << "pos: " << Simple_Search(s, sub) << endl;
	cout << "time " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << "ns" << endl;

	//RABIN-KARP SEARCH
	cout << "RK Search" << endl;
	time = chrono::high_resolution_clock::now();
	cout << "pos: " << RK_Search(s, sub) << endl;
	cout << "time " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << "ns" << endl;

	//HORSOOL SEARCH
	cout << "Horsool Search" << endl;
	time = chrono::high_resolution_clock::now();
	cout << "pos: " << Horsool_Search(s, sub) << endl;
	cout << "time " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << "ns" << endl;

	//BOYER-MOORE SEARCH
	cout << "Boyer-Moore Search" << endl;
	time = chrono::high_resolution_clock::now();
	cout << "pos: " << Boyer_Moore_Search(s, sub) << endl;
	cout << "time " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << "ns" << endl;

	//KNUTH-MORRIS-PRATTt SEARCH
	cout << "Knuth-Morris-Pratt Search" << endl;
	time = chrono::high_resolution_clock::now();
	cout << "pos: " << KMP_Search(s, sub) << endl;
	cout << "time " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << "ns" << endl;

	cout << "That's all Folks!" << endl;
	_getch();
	return 0;
}