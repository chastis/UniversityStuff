#include <cassert>
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <conio.h>

struct Point { int x, y; };

double distance(const Point &p1, const Point &p2)
{
	Point delta = { p2.x - p1.x, p2.y - p1.y };
	return std::sqrt((double)delta.x * delta.x + (double)delta.y * delta.y);
}

static std::vector<std::vector<double>> s_solutions;

double MWT(const Point poly[], unsigned n, unsigned i, unsigned j)
{
	assert(i < j && j < n);

	if (j == i + 1)
		// Исходное ребро - возвращаем вес 0
		return 0;

	if (s_solutions[i][j] >= 0)
		// Такую подзадачу мы уже решали - возвращаем готовое решение
		return s_solutions[i][j];

	// Такую подзадачу мы еще не решали - решаем ее полностью

	// Вес диагонали
	double weight_ij = i > 0 || j < n - 1 ? distance(poly[i], poly[j]) : 0;
	// Не забываем, что диагональ [0, n - 1] - это исходное ребро и ее вес равен 0

	double min_weight = std::numeric_limits<double>::max();
	for (unsigned k = i + 1; k < j; ++k)
	{
		double weight = MWT(poly, n, i, k) + MWT(poly, n, k, j);
		min_weight = std::min(min_weight, weight);
	}

	// Решение нашей подзадачи
	double weight = weight_ij + min_weight;

	// Запоминаем решение на будущее
	s_solutions[i][j] = weight;

	return weight;
}

double MWT(const Point poly[], unsigned n)
{
	return MWT(poly, n, 0, n - 1);
}

int main()
{
	Point poly[] = { { 0, 0 },{ 180, -50 },{ 195, -50 },{ 200, 0 },{ 195, 50 } };
	unsigned n = sizeof poly / sizeof *poly;

	s_solutions.resize(n);
	for (auto &s : s_solutions) s.resize(n, -1);

	std::cout << MWT(poly, n) << std::endl;
	std::cout << std::endl << "That's all Folks!" << std::endl;
	_getch();
	return 0;
}
/*

алгоритм сложный копец
чисто без пиваса не обойтись
для данного теста
Point poly[] = { { 0, 0 },{ 180, -50 },{ 195, -50 },{ 200, 0 },{ 195, 50 } };
					0			1			2			3			4
мы "типа" вырезаем наш многоугольничек из бумажечки
сначала мы начинаем с вершин 0 и 4
соседние вершины ничего не стоит вырезать (вес = 0)
что бы вырезать 0 и 4 запсукается такая рекурсия
0 1 // вес  = 0 // соседние вершины
1 4 //тут нужно считать и углубляться в рекурсию
как мы можем разрезать 1 и 4?
1 и 2//0
2 и 4
как мы можем разрезать 2 и 4?
2 и 3//0
3 и 4//0
значит 2 и 4 мы разрежим за 100 (рез между 2 и 4) + 0 (остальные резы)
возврщаемся к 1 и 4, значит мы можем разрезать через 1 2, 2 3, 3 4, 2 4.
на все это дело мы потратим 100 (рез между 2 и 4) и 101 (рез между 1 и 4)

попробуем по другому
как мы можем порезать 1 и 4?
1 и 3, а потом 3 и 4
как мы можем разрезать 1 и 3?
1 и 2//0
2 и 3//0
значит на 1 и 3 мы тратим  53 (рез между 1 и 3) + 0 (остальные резы)
3 и 4//0

возвращаемся к 1 и 4
мы получили новую суму резов : 53 + 101, которая меньше чем 100 + 101
обновим результат

на этом моменте мы возвращаемся к 0 и 4 с рузельтатом 154


и что вы думаете дальше?
правильно!
попробуем по другому 0 и 4
как?
0 2 и 2 4
и так далее


*/