#include <SFML/Graphics.hpp>
#include <vector>
namespace Global
{
	uint32_t modeWith = 800;
	uint32_t modeHeight = 600;
	float trueStep = 2.f;
	float interpStep = 0.1;
	float leftLimit = -6.f;
	float rightLimit = 6.f;
	float function(float x)
	{
		//return x * x * x + 3 * x * x + 3 * x + 1;
		return sin(x);
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

		break;
	}
	case InterpolationType::Cube:
	{

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
	std::vector<std::pair<float, float>> interpCoordinates;
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
			interpCoordinates.emplace_back(i, InterpTo<InterpolationType::Lagrange>(coordinates, i));
			i += Global::interpStep;
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
		findMaxMin(interpCoordinates, maxX, maxY, minX, minY);
		const float scaleX = (maxX - minX) ? Global::modeWith / (maxX - minX) : 1.f;
		const float scaleY = (maxY - minY) ? Global::modeHeight / (maxY - minY) : 1.f;
		sf::VertexArray lines(sf::LinesStrip);
		for (auto& coordinate : coordinates)
		{
			sf::Vertex vertex(sf::Vector2f((coordinate.first - minX) * scaleX, (coordinate.second - minY) * scaleY));
			lines.append(vertex);
		}
		sf::VertexArray interpLines(sf::LinesStrip);
		for (auto& coordinate : interpCoordinates)
		{
			sf::Vertex vertex(sf::Vector2f((coordinate.first - minX) * scaleX, (coordinate.second - minY) * scaleY), sf::Color::Blue);
			interpLines.append(vertex);
		}
		window.clear();
		window.draw(lines);
		window.draw(interpLines);
		window.display();
	}

	return 0;
}