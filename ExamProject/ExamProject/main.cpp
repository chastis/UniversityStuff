#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(800, 600), "Visual sort");
	window.display();
	std::cout << "Hello, world!" << std::endl;
	return 0;
}