#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <vector>

template <class T>
using Matrix = std::vector<std::vector<T>>;

namespace Global
{
	// gen param
	int32_t minRand = 0;
	int32_t maxRand = 1;
	uint32_t defaultSize = 100;
	// std out param
	uint32_t setW = 7;
	uint32_t precision = 3;
	// draw param
	float squareSize = 10.f;
	uint32_t modeWith = 1000;
	uint32_t modeHeight = 1000;
	// calc param
	float e = 0.0001f;
	float lambda = 0.01f;
	enum class MatrixType :uint8_t
	{
		random,
		diagonalDominant,
		gilbert,
		none
	};

	template <MatrixType type>
	void generateMatrix(Matrix<float>& matrix, uint32_t size = Global::defaultSize, bool additionalColumn = false)
	{
		matrix.resize(size);
		for (auto& line : matrix)
		{
			line.resize(size + additionalColumn);
		}

		float sum = 0.f;
		for (uint32_t i = 0; i < size; i++)
		{
			for (uint32_t j = 0; j < size + additionalColumn; j++)
			{
				switch (type)
				{
				case MatrixType::random:
				case MatrixType::diagonalDominant:
				{
					matrix[i][j] = std::rand() * 1.f / RAND_MAX * (Global::maxRand - Global::minRand) + Global::minRand;
					if (type == MatrixType::diagonalDominant)
					{
						sum += matrix[i][j];
					}
					break;
				}
				case MatrixType::gilbert:
				{
					matrix[i][j] = 1.0 / (i + j + 1.f);
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
			for (uint32_t i = 0; i < size; i++)
			{
				if (matrix[i][i] < sum)
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
				std::cout << std::setw(Global::setW) << std::setprecision(Global::precision) << std::fixed << element << " ";
			}
			std::cout << std::endl;
		}
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
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b)
{
	std::vector<T> out;
	uint32_t i = 0;
	for (; i < a.size() && i < b.size(); i++)
	{
		out.push_back(a[i] + b[i]);
	}
	for (; i < a.size(); i++)
	{
		out.push_back(a[i]);
	}
	for (; i < b.size(); i++)
	{
		out.push_back(b[i]);
	}
	return out;
}

template <class T>
std::vector<T> operator*(const std::vector<T>& a, const T& b)
{
	std::vector<T> out;
	for (uint32_t i = 0; i < a.size(); i++)
	{
		out.push_back(a[i] * b);
	}
	return out;
}

int main()
{
	// https://en.wikipedia.org/wiki/Algebraic_reconstruction_technique
	// http://www.imm.dtu.dk/~pcha/HDtomo/Day1algebraic.pdf
	// ??
	std::srand(std::time(nullptr));
	sf::RenderWindow window(sf::VideoMode(Global::modeWith, Global::modeHeight), "interpolation!");
	std::vector<float> xRED, bRED, xBLUE, bBLUE, xGREEN, bGREEN;
	xRED.resize(Global::defaultSize, 1.f);
	bRED.resize(Global::defaultSize, 1.f);
	xGREEN.resize(Global::defaultSize, 1.f);
	bRED.resize(Global::defaultSize);
	bBLUE.resize(Global::defaultSize);
	bGREEN.resize(Global::defaultSize);
	for (uint32_t i = 0; i < Global::defaultSize; i++)
	{
		bRED[i] = std::rand() * 1.f / RAND_MAX * (Global::maxRand - Global::minRand) + Global::minRand;
		bBLUE[i] = std::rand() * 1.f / RAND_MAX * (Global::maxRand - Global::minRand) + Global::minRand;
		bGREEN[i] = std::rand() * 1.f / RAND_MAX * (Global::maxRand - Global::minRand) + Global::minRand;
	}
	Matrix<float> RED, BLUE, GREEN;
	Global::generateMatrix<Global::MatrixType::random>(RED);
	Global::generateMatrix<Global::MatrixType::random>(GREEN);
	Global::generateMatrix<Global::MatrixType::random>(BLUE);
	uint64_t iteration = 0;
	while (window.isOpen())
	{
		sf::Event event = {};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		uint64_t k = iteration % Global::defaultSize;
		xRED = xRED + RED[k] * ((bRED[k] - RED[k] * xRED) / (RED[k] * RED[k])) * Global::lambda;
		xGREEN = xGREEN + GREEN[k] * ((bGREEN[k] - GREEN[k] * xGREEN) / (GREEN[k] * GREEN[k])) * Global::lambda;
		xBLUE = xBLUE + BLUE[k] * ((bBLUE[k] - BLUE[k] * xBLUE) / (BLUE[k] * BLUE[k])) * Global::lambda;
		for (const auto& el : xRED)
		{
			std::cout << std::setw(Global::setW) << std::setprecision(Global::precision) << std::fixed << el << " ";
		}
		std::cout << std::endl;
		window.clear();
		for (uint32_t i = 0; i < RED.size(); i++)
		{
			for (uint32_t j = 0; j < RED[i].size(); j++)
			{
				const float valueRED = RED[i][j] * xRED[j] * 255.f;
				const float valueBLUE = BLUE[i][j] * xBLUE[j] * 255.f;
				const float valueGREEN = GREEN[i][j] * xGREEN[j] * 255.f;
				sf::RectangleShape rectangle;
				rectangle.setSize(sf::Vector2f(Global::squareSize, Global::squareSize));
				rectangle.setPosition(i * Global::squareSize, j * Global::squareSize);
				rectangle.setFillColor(sf::Color(valueRED, valueGREEN, valueBLUE));
				window.draw(rectangle);
			}
		}
		window.display();
	}

	return 0;
}