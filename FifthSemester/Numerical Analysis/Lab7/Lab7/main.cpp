#include <SFML/Graphics.hpp>
#include <vector>
namespace Global
{
	uint32_t modeWith = 800;
	uint32_t modeHeight = 600;
	float trueStep = 2.f;
	float LagrangeInterpStep = 0.1;
	float NewtonInterpStep = 0.5;
	float CubeInterpStep = 0.1;
	float leftLimit = -6.f;
	float rightLimit = 6.f;
	float e = 0.0001f;
	float function(float x)
	{
		//return x * x * x + 3 * x * x + 3 * x + 1;
		return x * sin(5 * x);
	}
	int32_t GaussMethod(std::vector<std::vector<float>>& A, std::vector<float>& answer)
	{
		// https://e-maxx.ru/algo/linear_systems_gauss

		const uint32_t rowCount = A.size();
		const uint32_t columnCount = A[0].size() - 1;
		std::vector<float> find(columnCount, -1);

		for (uint32_t col = 0, row = 0; col < columnCount && row < rowCount; ++col) {
			uint32_t sel = row;
			for (uint32_t i = row; i < rowCount; ++i)
				if (std::abs(A[i][col]) > std::abs(A[sel][col]))
					sel = i;
			if (std::abs(A[sel][col]) < Global::e)
				continue;
			for (uint32_t i = col; i <= columnCount; ++i)
				std::swap(A[sel][i], A[row][i]);
			find[col] = row;

			for (uint32_t i = 0; i < rowCount; ++i)
				if (i != row) {
					const float c = A[i][col] / A[row][col];
					for (uint32_t j = col; j <= columnCount; ++j)
						A[i][j] -= A[row][j] * c;
				}
			++row;
		}

		answer.assign(columnCount, 0);
		for (uint32_t i = 0; i < columnCount; ++i)
			if (find[i] != -1)
				answer[i] = A[find[i]][columnCount] / A[find[i]][i];
		for (uint32_t i = 0; i < rowCount; ++i) {
			float sum = 0.f;
			for (uint32_t j = 0; j < columnCount; ++j)
				sum += answer[j] * A[i][j];
			if (std::abs(sum - A[i][columnCount]) > Global::e)
				return 0;
		}

		for (uint32_t i = 0; i < columnCount; ++i)
			if (find[i] == -1)
				return -1;
		return 1;
	}
}

enum class InterpolationType
{
	Lagrange,
	Newton,
	Cube,
	None
};

template<InterpolationType type>
float InterpTo(const std::vector<std::pair<float, float>>& coordinates, float x)
{
	float answer = 0;
	switch (type)
	{
	case InterpolationType::Lagrange:
	{
		// https://www.geeksforgeeks.org/lagranges-interpolation/
		for (uint32_t i = 0; i < coordinates.size(); i++)
		{
			float basicsPol = 1;
			for (uint32_t j = 0; j < coordinates.size(); j++)
			{
				if (j != i)
				{
					basicsPol *= (x - coordinates[j].first) / (coordinates[i].first - coordinates[j].first);
				}
			}
			answer += basicsPol * coordinates[i].second;
		}
		break;
	}
	case InterpolationType::Newton:
	{
		// https://www.geeksforgeeks.org/newtons-divided-difference-interpolation-formula/
		static bool isDiffCalculated = false;
		static std::vector<std::vector<float>> diffTable;
		if (!isDiffCalculated)
		{
			isDiffCalculated = true;
			diffTable.resize(coordinates.size());
			for (uint32_t i = 0; i < coordinates.size(); i++)
			{
				std::vector<float> temp;
				temp.resize(coordinates.size(), 0.f);
				temp[0] = coordinates[i].second;
				diffTable[i] = temp;

			}
			for (uint32_t i = 1; i < coordinates.size(); i++) {
				for (uint32_t j = 0; j < coordinates.size() - i; j++) {
					diffTable[j][i] = (diffTable[j][i - 1] - diffTable[j + 1][i - 1]) / (coordinates[j].first - coordinates[i + j].first);
				}
			}
		}

		// Function to find the product term 
		auto proterm = [&](uint32_t i, float value)
		{
			float pro = 1.f;
			for (uint32_t j = 0; j < i; j++) {
				pro *= value - coordinates[j].first;
			}
			return pro;
		};

		answer = diffTable[0][0];

		for (uint32_t i = 1; i < coordinates.size(); i++)
		{
			answer += (proterm(i, x) * diffTable[0][i]);
		}
		break;
	}
	case InterpolationType::Cube:
	{
		// http://blog.ivank.net/interpolation-with-cubic-splines.html

		static std::vector<float> ks;
		static bool isKsCalculated = false;
		if (!isKsCalculated)
		{
			isKsCalculated = true;

			uint32_t n = coordinates.size() - 1;

			std::vector<std::vector<float>> A;
			{
				std::vector<float> temp;
				temp.resize(n + 2, 0.f);
				A.resize(n + 1, temp);
			}

			for (uint32_t i = 1; i < n; i++)    // rows
			{
				A[i][i - 1] = 1 / (coordinates[i].first - coordinates[i - 1].first);

				A[i][i] = 2 * (1 / (coordinates[i].first - coordinates[i - 1].first) + 1 / (coordinates[i + 1].first - coordinates[i].first));

				A[i][i + 1] = 1 / (coordinates[i + 1].first - coordinates[i].first);

				A[i][n + 1] = 3 * ((coordinates[i].second - coordinates[i - 1].second) / ((coordinates[i].first - coordinates[i - 1].first) * (coordinates[i].first - coordinates[i - 1].first))
					+ (coordinates[i + 1].second - coordinates[i].second) / ((coordinates[i + 1].first - coordinates[i].first) * (coordinates[i + 1].first - coordinates[i].first)));
			}

			A[0][0] = 2 / (coordinates[1].first - coordinates[0].first);
			A[0][1] = 1 / (coordinates[1].first - coordinates[0].first);
			A[0][n + 1] = 3 * (coordinates[1].second - coordinates[0].second) / ((coordinates[1].first - coordinates[0].first) * (coordinates[1].first - coordinates[0].first));

			A[n][n - 1] = 1 / (coordinates[n].first - coordinates[n - 1].first);
			A[n][n] = 2 / (coordinates[n].first - coordinates[n - 1].first);
			A[n][n + 1] = 3 * (coordinates[n].second - coordinates[n - 1].second) / ((coordinates[n].first - coordinates[n - 1].first) * (coordinates[n].first - coordinates[n - 1].first));

			ks.resize(n + 1, 0.f);
			Global::GaussMethod(A, ks);
		}

		uint32_t i = 1;
		while (coordinates[i].first < x && i != coordinates.size() - 1) i++;

		float t = (x - coordinates[i - 1].first) / (coordinates[i].first - coordinates[i - 1].first);

		float a = ks[i - 1] * (coordinates[i].first - coordinates[i - 1].first) - (coordinates[i].second - coordinates[i - 1].second);
		float b = -ks[i] * (coordinates[i].first - coordinates[i - 1].first) + (coordinates[i].second - coordinates[i - 1].second);

		answer = (1 - t) * coordinates[i - 1].second + t * coordinates[i].second + t * (1 - t) * (a * (1 - t) + b * t);
		break;
	}
	default:;
	}


	return answer;
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(Global::modeWith, Global::modeHeight), "interpolation!");
	std::vector<std::pair<float, float>> coordinates;
	std::vector<std::pair<float, float>> lagrangeInterpCoordinates;
	std::vector<std::pair<float, float>> newtonInterpCoordinates;
	std::vector<std::pair<float, float>> cubeInterpCoordinates;
	//float i = Global::leftLimit;
	{
		float i = Global::leftLimit;
		while (i < Global::rightLimit)
		{
			coordinates.emplace_back(i, Global::function(i));
			i += Global::trueStep;
		}
		i = Global::leftLimit;
		while (i < Global::rightLimit)
		{
			lagrangeInterpCoordinates.emplace_back(i, InterpTo<InterpolationType::Lagrange>(coordinates, i));
			i += Global::LagrangeInterpStep;
		}
		i = Global::leftLimit;
		while (i < Global::rightLimit)
		{
			newtonInterpCoordinates.emplace_back(i, InterpTo<InterpolationType::Newton>(coordinates, i));
			i += Global::NewtonInterpStep;
		}
		i = Global::leftLimit;
		while (i < Global::rightLimit)
		{
			cubeInterpCoordinates.emplace_back(i, InterpTo<InterpolationType::Cube>(coordinates, i));
			i += Global::CubeInterpStep;
		}
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (coordinates.empty())
		{
			return 1;
		}
		float maxX = coordinates[0].first;
		float maxY = coordinates[0].second;
		float minX = coordinates[0].first;
		float minY = coordinates[0].second;

		auto findMaxMin = [](const std::vector<std::pair<float, float>>& coordinates, float& maxX, float& maxY, float& minX, float& minY)
		{
			for (const auto& point : coordinates)
			{
				if (point.first > maxX)
				{
					maxX = point.first;
				}
				if (point.second > maxY)
				{
					maxY = point.second;
				}
				if (point.first < minX)
				{
					maxX = point.first;
				}
				if (point.second < minY)
				{
					minY = point.second;
				}
			}
		};
		findMaxMin(coordinates, maxX, maxY, minX, minY);
		//findMaxMin(lagrangeInterpCoordinates, maxX, maxY, minX, minY);
		//findMaxMin(newtonInterpCoordinates, maxX, maxY, minX, minY);
		findMaxMin(cubeInterpCoordinates, maxX, maxY, minX, minY);
		const float scaleX = (maxX - minX) ? Global::modeWith / (maxX - minX) : 1.f;
		const float scaleY = (maxY - minY) ? Global::modeHeight / (maxY - minY) : 1.f;
		sf::VertexArray lines(sf::LinesStrip);
		for (auto& coordinate : coordinates)
		{
			sf::Vertex vertex(sf::Vector2f((coordinate.first - minX) * scaleX, (coordinate.second - minY) * scaleY));
			lines.append(vertex);
		}
		sf::VertexArray lagrangeInterpLines(sf::LinesStrip);
		for (auto& coordinate : lagrangeInterpCoordinates)
		{
			sf::Vertex vertex(sf::Vector2f((coordinate.first - minX) * scaleX, (coordinate.second - minY) * scaleY), sf::Color::Blue);
			lagrangeInterpLines.append(vertex);
		}
		sf::VertexArray newtonInterpLines(sf::LinesStrip);
		for (auto& coordinate : newtonInterpCoordinates)
		{
			sf::Vertex vertex(sf::Vector2f((coordinate.first - minX) * scaleX, (coordinate.second - minY) * scaleY), sf::Color::Green);
			newtonInterpLines.append(vertex);
		}
		sf::VertexArray cubeInterpLines(sf::LinesStrip);
		for (auto& coordinate : cubeInterpCoordinates)
		{
			sf::Vertex vertex(sf::Vector2f((coordinate.first - minX) * scaleX, (coordinate.second - minY) * scaleY), sf::Color::Yellow);
			cubeInterpLines.append(vertex);
		}
		window.clear();
		window.draw(lines);
		window.draw(lagrangeInterpLines);
		window.draw(newtonInterpLines);
		window.draw(cubeInterpLines);
		window.display();
	}

	return 0;
}