//https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%91%D1%80%D0%B5%D0%B7%D0%B5%D0%BD%D1%85%D1%8D%D0%BC%D0%B0
#include <SFML\Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	

	std::cout << "Enter R and coordinate of centre of circle" << std::endl;
	int R, X1, Y1;
	std::cin >> R >> X1 >> Y1;
	sf::VertexArray points;
	// R - радиус, X1, Y1 - координаты центра
	int x = 0;
	int y = R;
	int delta = 1 - 2 * R;
	int error = 0;
	while (y >= 0) {
		points.append(sf::Vector2f(X1 + x, Y1 + y));
		points.append(sf::Vector2f(X1 + x, Y1 - y));
		points.append(sf::Vector2f(X1 - x, Y1 + y));
		points.append(sf::Vector2f(X1 - x, Y1 - y));
		error = 2 * (delta + y) - 1;
		if ((delta < 0) && (error <= 0)) {
			delta += 2 * ++x + 1;
			continue;
		}
		if ((delta > 0) && (error > 0)) {
			delta -= 2 * --y + 1;
			continue;
		}
		delta += 2 * (++x - y--);
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(points);
		window.display();
	}

	return 0;
}
