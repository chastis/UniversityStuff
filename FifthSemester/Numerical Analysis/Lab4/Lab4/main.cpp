#include <iostream>
#include <vector>
#include <conio.h>
#include <iomanip>
//#include <windows.h>
#include <iterator>

template <class T>
using Matrix = std::vector<std::vector<T>>;

namespace Global
{
	int32_t minRand = 1;
	int32_t maxRand = 10;
	uint32_t defaultSize = 3;
	uint32_t setW = 7;
	uint32_t precision = 3;
	float e = 0.00001f;
}

enum class MatrixType :uint8_t
{
	random,
	diagonalDominant,
	gilbert,
	cin,
	none
};

template <MatrixType type, class T>
void generateMatrix(Matrix<T>& outMatrix, uint32_t sizeLines = Global::defaultSize, uint32_t sizeColumns = Global::defaultSize)
{
	outMatrix.resize(sizeLines);
	for (auto& line : outMatrix)
	{
		line.resize(sizeColumns);
	}

	T sum = static_cast<T>(0);
	for (uint32_t i = 0; i < sizeLines; i++)
	{
		for (uint32_t j = 0; j < sizeColumns; j++)
		{
			switch (type)
			{
			case MatrixType::random:
			case MatrixType::diagonalDominant:
			{
				if (std::is_floating_point_v<T>)
				{

					outMatrix[i][j] = std::rand() * 1.0 / RAND_MAX * (Global::maxRand - Global::minRand) + Global::minRand;
				}
				else if (std::is_integral_v<T>)
				{
					outMatrix[i][j] = std::rand() % (Global::maxRand - Global::minRand) + Global::minRand;
				}
				if (type == MatrixType::diagonalDominant)
				{
					sum += outMatrix[i][j];
				}
				break;
			}
			case MatrixType::gilbert:
			{
				outMatrix[i][j] = 1.0 / (i + j + 1);
				break;
			}
			case MatrixType::cin:
			{
				std::cin >> outMatrix[i][j];
				break;
			}
			default:
			{
				// no entry
			}
			}
		}
	}

	if (MatrixType::diagonalDominant == type)
	{
		for (uint32_t i = 0; i < sizeLines; i++)
		{
			if (outMatrix[i][i] < sum)
			{
				outMatrix[i][i] += sum;
			}
		}
	}

}

template <class T>
void generateVector(bool isRandom, std::vector<T>& outVector, uint32_t size = Global::defaultSize)
{
	outVector.resize(size);
	for (auto& element : outVector)
	{
		if (isRandom)
		{
			if (std::is_floating_point_v<T>)
			{
				element = std::rand() * 1.0 / RAND_MAX * (Global::maxRand - Global::minRand) + Global::minRand;
			}
			else if (std::is_integral_v<T>)
			{
				element = std::rand() % (Global::maxRand - Global::minRand) + Global::minRand;
			}
		}
		else
			element = static_cast<T>(1.f);
	}
}
template <class T>
void printMatrix(const Matrix<T>& matrix)
{
	for (const auto& line : matrix)
	{
		for (const auto& element : line)
		{
			std::cout << std::setw(Global::setW) << std::setprecision(Global::precision) << std::fixed << element << " ";
		}
		std::cout << std::endl;
	}
}
template <class T>
T operator*(const std::vector<T>& a, const std::vector<T>& b)
{
	T scalar = static_cast<T>(0);
	if (a.size() == b.size() && !a.empty())
	{
		for (uint32_t i = 0; i < a.size(); i++)
		{
			scalar += a[i] * b[i];
		}
	}
	return scalar;
}

template <class T>
class SLE
{
public:
	Matrix<T> a;
	std::vector<T> b;
	std::vector<T> x;
	template <MatrixType type>
	void init(uint32_t size = Global::defaultSize)
	{
		generateMatrix<type, T>(a, size, size);
		generateVector<T>(false, x, size);
		b.resize(size);
		for (uint32_t i = 0; i < size; i++)
		{
			b[i] = x * a[i];
		}
		generateVector<T>(true, x, size);
	}
	int32_t GaussMethod()
	{
		// https://e-maxx.ru/algo/linear_systems_gauss

		Matrix<T> extended;
		extended.reserve(a.size());
		x.resize(a.size());
		std::copy(a.begin(), a.end(), std::back_inserter(extended));
		for (uint32_t i = 0; i < a.size(); i++)
		{
			extended[i].push_back(b[i]);
		}

		const uint32_t rowCount = a.size();
		const uint32_t columnCount = a.size();
		std::vector<T> find(columnCount, -1);

		for (uint32_t col = 0, row = 0; col < columnCount && row < rowCount; ++col) {
			uint32_t sel = row;
			for (uint32_t i = row; i < rowCount; ++i)
				if (std::abs(extended[i][col]) > std::abs(extended[sel][col]))
					sel = i;
			if (std::abs(extended[sel][col]) < Global::e * Global::e * Global::e)
				continue;
			for (uint32_t i = col; i <= columnCount; ++i)
				std::swap(extended[sel][i], extended[row][i]);
			find[col] = row;

			for (uint32_t i = 0; i < rowCount; ++i)
				if (i != row) {
					T c = extended[i][col] / extended[row][col];
					for (uint32_t j = col; j <= columnCount; ++j)
						extended[i][j] -= extended[row][j] * c;
				}
			++row;
		}

		x.assign(columnCount, 0);
		for (uint32_t i = 0; i < columnCount; ++i)
			if (find[i] != -1)
				x[i] = extended[find[i]][columnCount] / extended[find[i]][i];
		for (uint32_t i = 0; i < rowCount; ++i) {
			T sum = static_cast<T>(0);
			for (uint32_t j = 0; j < columnCount; ++j)
				sum += x[j] * extended[i][j];
			if (std::abs(sum - extended[i][columnCount]) > Global::e)
				return 0;
		}

		for (uint32_t i = 0; i < columnCount; ++i)
			if (find[i] == -1)
				return -1;
		return 1;
	}
	int32_t JakobiMethod()
	{
		// https://ru.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%AF%D0%BA%D0%BE%D0%B1%D0%B8
		std::vector<T> tempX;
		tempX.resize(a.size());
		x.resize(a.size());
		T norm = static_cast<T>(0); // норма, определяемая как наибольшая разность компонент столбца иксов соседних итераций.

		do {
			for (uint32_t i = 0; i < a.size(); i++)
			{
				tempX[i] = b[i];
				for (uint32_t g = 0; g < a.size(); g++)
				{
					if (i != g)
						tempX[i] -= a[i][g] * x[g];
				}
				tempX[i] /= a[i][i];
			}
			norm = std::fabs(x[0] - tempX[0]);
			for (uint32_t h = 0; h < a.size(); h++)
			{
				if (std::fabs(x[h] - tempX[h]) > norm)
					norm = std::fabs(x[h] - tempX[h]);
				x[h] = tempX[h];
			}
		} while (norm > Global::e);
		return 1;
	}
	int32_t SeidelMethod()
	{
		/// https://uk.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%93%D0%B0%D1%83%D1%81%D0%B0_%E2%80%94_%D0%97%D0%B5%D0%B9%D0%B4%D0%B5%D0%BB%D1%8F
		// Умова завершення
		auto converge = [](const std::vector<T>& xk, const std::vector<T>& xkp)
		{
			bool b = true;
			for (uint32_t i = 0; i < xk.size(); i++)
			{
				if (std::fabs(xk[i] - xkp[i]) > Global::e)
				{
					b = false;
					break;
				}
			}
			return b;
		};

		std::vector<T> p;
		p.resize(x.size());
		do
		{
			for (uint32_t i = 0; i < a.size(); i++)
			{
				T var = static_cast<T>(0);
				for (uint32_t j = 0; j < a.size(); j++)
				{
					if (j != i)
						var += (a[i][j] * x[j]);
				}
				p[i] = x[i];
				x[i] = (b[i] - var) / a[i][i];
			}
			for (const auto& el : x)
			{
				std::cout << el << " ";
			}
			std::cout << std::endl;
		} while (!converge(x, p));
		return 1;
	}
	void compareSolutions()
	{
		std::cout << "b - a" << std::endl;
		for (uint32_t i = 0; i < a.size(); i++)
		{
			T temp = a[i] * x;
			std::cout << b[i] - temp << " ";
		}
		std::cout << std::endl;
	}
};

int main()
{
	SLE<float> sle;
	sle.init<MatrixType::gilbert>();
	std::vector<float> answer;
	std::cout << "Answer's count " << sle.SeidelMethod() << std::endl;
	for (const auto& element : sle.x)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl << "Matrix:" << std::endl;
	printMatrix<float>(sle.a);
	sle.compareSolutions();

	_getch();
	return 0;
}
