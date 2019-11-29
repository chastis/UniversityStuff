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
	int32_t maxRand = 10;
	uint32_t defaultSize = 3;
	uint32_t setW = 7;
	uint32_t precision = 3;
	float e = 0.0001f;
	float defaultMatrixValue = 1.f;
}

enum class MatrixType :uint8_t
{
	random,
	diagonalDominant,
	gilbert,
	randomSymmetrical,
	defaultValue,
	none
};

template <MatrixType type, class T>
void generateMatrix(Matrix<T>& matrix, uint32_t size = Global::defaultSize)
{
	matrix.resize(size);
	for (auto& line : matrix)
	{
		line.resize(size);
	}

	T sum = static_cast<T>(0);
	for (uint32_t i = 0; i < size; i++)
	{
		for (uint32_t j = 0; j < size; j++)
		{
			switch (type)
			{
			case MatrixType::random:
			case MatrixType::randomSymmetrical:
			case MatrixType::diagonalDominant:
			{
				if (std::is_floating_point_v<T>)
				{

					matrix[i][j] = std::rand() * 1.0 / RAND_MAX * (Global::maxRand - Global::minRand) + Global::minRand;
				}
				if (std::is_integral_v<T>)
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
			case MatrixType::defaultValue:
			{
				matrix[i][j] = Global::defaultMatrixValue;
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
		for (uint32_t i = 0; i < size; i++)
		{
			if (matrix[i][i] < sum)
			{
				matrix[i][i] += sum;
			}
		}
	}

	if (MatrixType::randomSymmetrical == type)
	{
		for (uint32_t i = 0; i < size; i++)
		{
			for (uint32_t j = i + 1; j < size; j++)
			{
				matrix[i][j] = matrix[j][i];
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
			std::cout << std::setw(Global::setW) << std::setprecision(Global::precision) << std::fixed << element << " ";
		}
		std::cout << std::endl;
	}
}

bool isSymmetrical(const Matrix<float>& coefficients)
{
	for (uint32_t i = 0; i < coefficients.size(); i++)
	{
		for (uint32_t j = i + 1; j < coefficients.size(); j++)
		{
			if (coefficients[i][j] != coefficients[j][i])
			{
				return false;
			}
		}
	}
	return true;
}
int32_t JacobiRotation(Matrix<float>& coefficients, Matrix<float>& solution)
{
	const uint32_t n = coefficients.size();
	int32_t result = 1;
	uint32_t i, j, k;
	uint32_t maxI = 0, maxJ = 0;
	Matrix<float> rotationMatrix;
	Matrix<float> temp;
	{
		std::vector<float> empty;
		empty.resize(n, 0.f);
		rotationMatrix.resize(n, empty);
		temp.resize(n, empty);

	}
	float fault = 0.0;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			fault = fault + coefficients[i][j] * coefficients[i][j];
		}
	}
	fault = sqrt(2 * fault);
	while (fault > Global::e) {
		std::cout << "it" << std::endl;
		printMatrix(coefficients);
		float max = 0.f;
		for (i = 0; i < n; i++)
		{
			for (j = i + 1; j < n; j++)
			{
				if (coefficients[i][j] > 0 && coefficients[i][j] > max)
				{
					max = coefficients[i][j];
					maxI = i;
					maxJ = j;
				}
				else if (coefficients[i][j] < 0 && -coefficients[i][j] > max)
				{
					max = -coefficients[i][j];
					maxI = i;
					maxJ = j;
				}
			}
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				rotationMatrix[i][j] = 0;
			}
			rotationMatrix[i][i] = 1;
		}
		if (coefficients[maxI][maxI] == coefficients[maxJ][maxJ])
		{
			rotationMatrix[maxI][maxI] = rotationMatrix[maxJ][maxJ] =
				rotationMatrix[maxJ][maxI] = sqrt(2.0) / 2.0;
			rotationMatrix[maxI][maxJ] = -sqrt(2.0) / 2.0;
		}
		else
		{
			const float fi = 0.5f * atan((2.0 * coefficients[maxI][maxJ]) /
				(coefficients[maxI][maxI] - coefficients[maxJ][maxJ]));
			rotationMatrix[maxI][maxI] = rotationMatrix[maxJ][maxJ] = cos(fi);
			rotationMatrix[maxI][maxJ] = -sin(fi);
			rotationMatrix[maxJ][maxI] = sin(fi);
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				temp[i][j] = 0.0;
			}
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				for (k = 0; k < n; k++)
				{
					temp[i][j] = temp[i][j] + rotationMatrix[k][i] * coefficients[k][j];
				}
			}
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				coefficients[i][j] = 0.f;
			}
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				for (k = 0; k < n; k++)
				{
					coefficients[i][j] = coefficients[i][j] +
						temp[i][k] * rotationMatrix[k][j];
				}
			}
		}
		fault = 0.f;
		for (i = 0; i < n; i++)
		{
			for (j = i + 1; j < n; j++)
			{
				fault = fault + coefficients[i][j] * coefficients[i][j];
			}
		}
		fault = sqrt(2 * fault);
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				temp[i][j] = 0.0;
			}
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				for (k = 0; k < n; k++)
				{
					temp[i][j] = temp[i][j] + solution[i][k] * rotationMatrix[k][j];
				}
			}
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				solution[i][j] = temp[i][j];
			}
		}
		result++;
	}
	return result;
}

int main()
{
	// https://ru.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%AF%D0%BA%D0%BE%D0%B1%D0%B8_%D0%B4%D0%BB%D1%8F_%D1%81%D0%BE%D0%B1%D1%81%D1%82%D0%B2%D0%B5%D0%BD%D0%BD%D1%8B%D1%85_%D0%B7%D0%BD%D0%B0%D1%87%D0%B5%D0%BD%D0%B8%D0%B9
	// http://www.cyberforum.ru/cpp-beginners/thread701320.html
	std::vector<std::vector<float>> coefficients, solution;
	generateMatrix<MatrixType::randomSymmetrical, float>(coefficients);
	generateMatrix<MatrixType::defaultValue, float>(solution);
	if (!isSymmetrical(coefficients)) {
		std::cout << "Matrix is not symmetrical\n";
	}
	else
	{
		std::cout << "In Matrix :" << std::endl;
		printMatrix(coefficients);
		const int32_t steps = JacobiRotation(coefficients, solution);
		std::cout << "Solution:\n";
		for (uint32_t i = 0; i < solution.size(); i++) {
			std::cout << "Vector k : " << i + 1 << ":\n";
			for (uint32_t j = 0; j < solution.size(); j++) {
				std::cout << solution[j][i] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "Eigenvalues:\n";
		for (uint32_t i = 0; i < solution.size(); i++) {
			std::cout << coefficients[i][i] << "\n";
		}
		std::cout << "Steps: " << steps;
	}

	_getch();
	return 0;
}
