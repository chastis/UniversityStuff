#ifndef MENU_H
#define MENU_H

#include "helpers.h"
#include "Visualizer.h"
#include "Data.h"
#include "Sortings.h"

class Buttons
{
public:
	friend class Menu;
	Buttons();
	~Buttons();
	Buttons(std::string name, int x, int y, bool visible = false);
	//is visible?
	bool is_visible();
	//is this point in our sprite?
	bool contain(int x, int y);
	//draw
	void draw(sf::RenderWindow &window);
	//is purple?
	bool is_shine();
protected:
	//painting button into turquoise 
	void change_color();
	//painting button into purple
	void shine_color();
	//reset original color
	void return_color();
	//name of file with sprite
	std::string _name;
	//sfml
	sf::Texture _texture;
	sf::Sprite _sprite;
	//visible or not in the menu
	bool _visible;
	//shine mean is purple?
	bool _shine;
};

class Menu
{
public:
	Menu();
	~Menu();
	//do menu open?
	bool is_menu();
	//reset and open menu
	void open();
	//close menu
	void close();
	//check is mouse in the buttons or not
	void change_colors(sf::Vector2f pos);
	//draw menu
	void draw(sf::RenderWindow &window, long long size);
	//check buttons for pressed
	//do all button's work
	void work(sf::Vector2f pos, sf::RenderWindow &window, long long &size, sort_type &type, Visualizer &vis);
	//reset to fisrt menu page
	void reset();
private:
	//menu are showing
	bool _is_menu;
	//sfml staff
	std::vector<Buttons * > _buttons;
};

#endif // !MENU_H
