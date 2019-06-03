#include "helpers.h"
#include "Visualizer.h"
#include "Sortings.h"
#include "Menu.h"

using namespace sf;

void sort(Data& d) {
	std::sort(d.begin(), d.end(), Data::comp);
}

int main()
{
	RenderWindow window(VideoMode(800, 600), "Visual sort");
	Menu menu;
	sort_type current_type;
	long long size = 100;
	Data d(10, 500, 1000);
	Visualizer visualizer(d);
	visualizer.setSize({800, 50});
	visualizer.setPosition({0, 300});

	//visualizer.sort(std::sort<decltype(d.begin()), decltype(_comp)>, _comp);
	//visualizer.sort(s.getBubbleSort(), _comp);
	//for only one time esc has been pressed
	bool esc_pressed = false;
	while (window.isOpen())
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window); //coord of mouse (in px)
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos); //coord of mous (transform)
		//if we pressed esc we come to menu
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !esc_pressed)
		{
			esc_pressed = true;
			//esc in the menu return us at home
			if (menu.is_menu())
			{
				menu.reset();
			}
			//open menu;
			else
			{
				menu.reset();
				menu.open();
			}
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && esc_pressed)
		{
			esc_pressed = false;
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			visualizer.check_mutex();
			Data d(10, 500, 1000);
			visualizer.setData(d);
			visualizer.setSize({ 800, 50 });
			visualizer.setPosition({ 0, 500 });
			//visualizer.sort(s.getBubbleSort(), _comp);
		}
		Event event;

		
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
			{
				window.close();
			}

			
			if (menu.is_menu())
			{
				//try to change color of menu's buttons
				menu.change_colors(pos);
				//pressed left mouse
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.key.code == sf::Mouse::Left)
					{
						menu.work(pos, window, size, current_type, visualizer);

						
					}
				}

			}
			else
			{
				
			}
		}
		

		window.clear();
		if (menu.is_menu())
		{
			menu.draw(window, size);
		}
		else window.draw(visualizer);
		window.display();
	}
	return 0;
}