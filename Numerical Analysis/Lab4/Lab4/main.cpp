#include <iostream>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <windows.h>

template <class T>
using Matrix = std::vector<std::vector<T>>;

namespace Global
{
	int32_t minRand = 1;
	int32_t maxRand = 100;
	uint32_t defaultSize = 10;
	uint32_t setW = 7;
	uint32_t precision = 3;
}

enum class MatrixType:uint8_t
{
	random,
	diagonalDominant,
	gilbert,
	none
};

template <MatrixType type, class T>
void generateMatrix(Matrix<T>& matrix, uint32_t sizeLines = Global::defaultSize, uint32_t sizeColumns = Global::defaultSize)
{
	matrix.resize(sizeLines);
	for (auto& line : matrix)
	{
		line.resize(sizeColumns);
	}

	T sum = static_cast<T>(0);
	for (uint32_t i = 0; i < sizeLines ; i++)
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
						
						matrix[i][j] = std::rand() * 1.0 / RAND_MAX * (Global::maxRand - Global::minRand) + Global::minRand;
					}
					else if (std::is_integral_v<T>)
					{
						matrix[i][j] = std::rand() % (Global::maxRand - Global::minRand) + Global::minRand;
					}
					if (type == MatrixType::diagonalDominant)
					{
						sum += matrix[i][j];
					}
					break;
				}
				case MatrixType::gilbert:
				{
					matrix[i][j] = 1.0 / (i + j + 1);
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
			if (matrix[i][i]<sum)
			{
				matrix[i][i] += sum;
			}
		}
	}

}

template <class T>
void printMatrix(const Matrix<T>& matrix)
{
	for (const auto& line : matrix)
	{
		for (const auto& element : line)
		{
			std::cout  << std::setw(Global::setW) << std::setprecision(Global::precision) << std::fixed << element << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	std::vector<std::vector<float>> matrix;
	std::cout << "Random matrix:\n";
	generateMatrix<MatrixType::random, float>(matrix);
	printMatrix<float>(matrix);
	std::cout << "Diagonal matrix:\n";
	generateMatrix<MatrixType::diagonalDominant, float>(matrix);
	printMatrix<float>(matrix);
	std::cout << "Gilbert matrix:\n";
	generateMatrix<MatrixType::gilbert, float>(matrix);
	printMatrix<float>(matrix);




	_getch();
	return 0;
}
