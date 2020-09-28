#include <iostream>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <windows.h>

template <class T>
using Matrix = std::vector<std::vector<T>>;

namespace Global
{
	uint32_t defaultSize = 10;
	uint32_t setW = 4;
	uint32_t precision = 2;
	float defaultMatrixValue = 0.f;
	float e = 0.00001;
}

enum class MatrixType :uint8_t
{
	graph,
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
			case MatrixType::graph:
			{
				matrix[i][j] = std::rand() % 2;
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

	if (MatrixType::graph == type)
	{
		for (uint32_t i = 0; i < size; i++)
		{
			matrix[i][i] = 0;
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

int32_t main()
{
	// https://www.cs.usfca.edu/~cruse/math202s11/pagerank.cpp
	// best video about this algorithm https://www.youtube.com/watch?v=kSmQbVxqOJc 
	// good pdf presentation by google https://web.stanford.edu/class/cs54n/handouts/24-GooglePageRankAlgorithm.pdf
	std::vector<std::vector<bool>> digraph;
	std::vector<std::vector<float>> transition;
	std::cout << "Graph:\n";
	generateMatrix<MatrixType::graph, bool>(digraph);
	generateMatrix<MatrixType::defaultValue, float>(transition);
	printMatrix<bool>(digraph);

	// compute entries for the corresponding transition matrix
	for (uint32_t i = 0; i < Global::defaultSize; i++)
	{
		uint32_t rowsum = 0;
		for (uint32_t j = 0; j < Global::defaultSize; j++) rowsum += digraph[i][j];
		if (rowsum > 0)
			for (uint32_t j = 0; j < Global::defaultSize; j++)
				transition[i][j] = static_cast<float>(digraph[i][j]) / rowsum;
		else	// A fixup for the "dangling node" problem
			for (uint32_t j = 0; j < Global::defaultSize; j++)
				transition[i][j] = 1.0 / Global::defaultSize;
	}

	// display the specified transition matrix
	std::cout << "Here is the corresponding Transition Matrix: " << std::endl;
	for (uint32_t i = 0; i < Global::defaultSize; i++)
	{
		for (uint32_t j = 0; j < Global::defaultSize; j++)
			std::cout << transition[i][j] << " ";
		std::cout << std::endl;
	}

	// recompute the transition matrix entries
	const float alpha = 0.85f;
	for (uint32_t i = 0; i < Global::defaultSize; i++)
		for (uint32_t j = 0; j < Global::defaultSize; j++)
		{
			float entry = transition[i][j];
			entry = (alpha * entry) + ((1.f - alpha) / Global::defaultSize);
			transition[i][j] = entry;
		}

	// display the modified transition matrix
	std::cout << "Here is the adjusted Transition Matrix: " << std::endl;
	for (uint32_t i = 0; i < Global::defaultSize; i++)
	{
		for (uint32_t j = 0; j < Global::defaultSize; j++)
			std::cout << transition[i][j] << " ";
		std::cout << std::endl;
	}

	// initialize the current matrix power
	Matrix<float> current;
	generateMatrix<MatrixType::defaultValue, float>(current);
	for (uint32_t i = 0; i < Global::defaultSize; i++)
		for (uint32_t j = 0; j < Global::defaultSize; j++)
			current[i][j] = (i == j) ? 1.f : 0.f;

	//----------------------------------------------------
	// main loop to display the sequence of matrix powers
	//----------------------------------------------------
	uint32_t step = 0;
	do
	{
		// compute the next matrix power 
		Matrix<float> product;
		generateMatrix<MatrixType::defaultValue, float>(product);
		for (uint32_t i = 0; i < Global::defaultSize; i++)
			for (uint32_t j = 0; j < Global::defaultSize; j++)
			{
				float sum = 0.f;
				for (uint32_t k = 0; k < Global::defaultSize; k++)
					sum += current[i][k] * transition[k][j];
				product[i][j] = sum;
			}
		for (uint32_t i = 0; i < Global::defaultSize; i++)
			for (uint32_t j = 0; j < Global::defaultSize; j++)
				current[i][j] = product[i][j];

		// display the current matrix power
		std::cout << "The Transition Matrix to power " << step + 1 << std::endl;
		for (uint32_t i = 0; i < Global::defaultSize; i++)
		{
			for (uint32_t j = 0; j < Global::defaultSize; j++)
				std::cout << current[i][j] << " ";
			std::cout << std::endl;
		}

		// see if the stationary vector has been reached yet
		float square_diff = 0.0;
		for (uint32_t j = 0; j < Global::defaultSize; j++)
			for (uint32_t i = 1; i < Global::defaultSize; i++)
			{
				const float diff = (current[i][j] - current[0][j]);
				square_diff += diff * diff;
			}
		if (square_diff < Global::e) break;
		step++;
	} while (true);
	std::cout << std::endl;

	// display the stationary vector with the node-name letters	
	std::vector<float> rank(Global::defaultSize);
	std::vector<uint32_t> node(Global::defaultSize);
	for (uint32_t j = 0; j < Global::defaultSize; j++)
	{
		node[j] = j;
		rank[j] = current[0][j];
	}
	std::cout << "Here is the resulting stationary vector: \n";
	for (uint32_t j = 0; j < Global::defaultSize; j++) std::cout << rank[j] << " ";
	std::cout << std::endl;
	for (uint32_t j = 0; j < Global::defaultSize; j++) std::cout << node[j] << " ";
	std::cout << std::endl;

	// perform a bubble-sort on the stationary vector's components
	{
		uint32_t i = 0, j = 1;
		do {
			if (rank[i] < rank[j])
			{
				const float temp_i = rank[i];
				const float temp_j = rank[j];
				rank[i] = temp_j;
				rank[j] = temp_i;
				const uint32_t node_i = node[i];
				const uint32_t node_j = node[j];
				node[i] = node_j;
				node[j] = node_i;
				i = 0;
				j = 1;
			}
			else {
				++i;
				++j;
			}
		} while (j < Global::defaultSize);
	}
	// display the stationary vector's components in sorted order 	
	std::cout << "Here is the resulting Rage-Punk vector: \n";
	for (uint32_t j = 0; j < Global::defaultSize; j++) std::cout << rank[j] << " ";
	std::cout << std::endl;
	for (uint32_t j = 0; j < Global::defaultSize; j++) std::cout << node[j] << " ";
	std::cout << std::endl;

	_getch();
	return 0;
}
