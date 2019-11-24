#include "String_Searching_Algorithm.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#define ALPHABET 256
using namespace std;

int Simple_Search(const string &where, const string &what) {
	int n = where.length();
	int m = what.length();
	// Внешний цикл поиска в исходной строке
	for (int i = 0; i <= n - m; i++) {
		// Внутренний цикл сравнения:
		bool flag = true;
		for (int j = 0; j < m; j++) {
			if (where[i + j] != what[j]) {
				flag = false;
				break;
			}
		}
		if (flag) return i;
	}
	return -1;
}

int RK_Search(const string &where, const string &what) {
	// считаем все степени p
	//p - простое число
	const int p = 31;
	vector<long long> p_pow(max(what.length(), where.length()));
	p_pow[0] = 1;
	for (size_t i = 1; i<p_pow.size(); ++i)
		p_pow[i] = p_pow[i - 1] * p;

	// считаем хэши от всех префиксов строки "where"
	vector<long long> h(where.length());
	for (size_t i = 0; i<where.length(); ++i)
	{
		h[i] = (where[i] - 'a' + 1) * p_pow[i];
		if (i)  h[i] += h[i - 1];
	}

	// считаем хэш от строки "what"
	long long h_s = 0;
	for (size_t i = 0; i<what.length(); ++i)
		h_s += (what[i] - 'a' + 1) * p_pow[i];

	// перебираем все подстроки "where" длины |what| и сравниваем их
	for (size_t i = 0; i + what.length() - 1 < where.length(); ++i)
	{
		long long cur_h = h[i + what.length() - 1];
		if (i)  cur_h -= h[i - 1];
		// приводим хэши к одной степени и сравниваем
		if (cur_h == h_s * p_pow[i])
			return i;
	}

	return -1;
}

bool compare(string::const_iterator a,const string::const_iterator b, int num) {
	for (auto i = a, j = b; i < a + num; i++, j++) {
		if (*i != *j) return false;
	}
	return true;
}

int Horsool_Search(const string &where, const string &what)
{
	unsigned int skip_table[ALPHABET];
	int i;


	/*предварительная обработка */
	/** заполнить таблицу максимальным значением прыжка */
	for (i = 0; i < ALPHABET; i++)
		skip_table[i] = what.size();

	/** затем вычислить для каждого символа шаблона скачок */
	for (i = 0; i < what.size() - 1; i++)
		skip_table[(int)what[i]] = what.size() - i - 1;

	/* поиск */
	i = 0;
	while (i <= where.size() - what.size()) {
		if (where[i + what.size() - 1] == what[what.size() - 1])
			if (compare(where.begin() + i, what.begin(), what.size() - 2) == true)
				return i;

		/* если эти два символа отличаются друг от друга,
		прыгаем, используя значение таблицы перехода в
		индекс символа текста */
		i += skip_table[(int)where[i + what.size() - 1]];
	}

	return -1;
}

int Boyer_Moore_Search(const string &where, const string &what){
	//свдиг хорошего суффикса
	vector<int> good_shift(what.size() + 1, what.size());
	//сдвиг плохого символа
	vector<int> bad_char(ALPHABET, what.size());

	//предварительно
	//массив Z, каждый элемент которого Z[i] равен длине наиболее длинного префикса суффикса подстроки,
	//начинающегося с позиции i в строке S, который одновременно является и префиксом всей строки S
	vector<int> z(what.size(), 0);
	for (int j = 1, maxZidx = 0, maxZ = 0; j < what.size(); ++j) {
		if (j <= maxZ) z[j] = min(maxZ - j + 1, z[j - maxZidx]);
		while (j + z[j] < what.size() && where[what.size() - 1 - z[j]] == where[what.size() - 1 - (j + z[j])]) z[j]++;
		if (j + z[j] - 1 > maxZ) {
			maxZidx = j;
			maxZ = j + z[j] - 1;
		}
	}
	for (int j = what.size() - 1; j > 0; j--) good_shift[what.size() - z[j]] = j; //цикл №1
	for (int j = 1, r = 0; j <= what.size() - 1; j++) //цикл №2
		if (j + z[j] == what.size())
			for (; r <= j; r++)
				if (good_shift[r] == what.size()) good_shift[r] = j;

	//
	for (int j = 0; j < what.size() - 1; j++) bad_char[(int)what[j]] = what.size() - j - 1;


	//loop
	int i = 0;
	while (i <= what.size() - where.size()) {
		int j = 0;
		for (j = what.size() - 1; j >= 0 && what[j] == where[i + j]; --j);
		if (j < 0) {
			return i;
		}
		else i += max((good_shift[j + 1]), (int)(bad_char[(int)where[i + j]] - what.size() + j + 1));
	}
	return -1;
}

int KMP_Search(const string &where, const string what) {
	vector<int> z;
	//считаем з-функцию
	z.resize(what.size());
	z[0] = 0;
	for (int i = 1; i<z.size(); ++i) {
		int pos = z[i - 1];
		while (pos > 0 && what[pos] != what[i])
			pos = z[pos - 1];
		z[i] = pos + (what[pos] == what[i] ? 1 : 0);
	}
	//посчитали

	int pos = 0;
	for (int i = 0; i<where.size(); ++i) {
		while (pos > 0 && (pos >= what.size() || what[pos] != where[i]))
			pos = z[pos - 1];
		if (where[i] == what[pos]) pos++;
		if (pos == what.size())
			return (i - pos + 1);
	}
	return -1;
}