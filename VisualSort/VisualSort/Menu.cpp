#include "Menu.h"


Buttons::Buttons()
{
	_name = "";
	_texture; _sprite;
}

Buttons::~Buttons()
{

}

Buttons::Buttons(std::string name, int x, int y, bool visible)
{
	_visible = visible;
	_shine = false;
	_name = name;
	_texture.loadFromFile("images/" + name);
	_sprite.setTexture(_texture);
	//take center
	_sprite.setPosition(x - _texture.getSize().x / 2, y - _texture.getSize().y / 2);
}

bool Buttons::is_visible()
{
	return _visible;
}

bool Buttons::contain(int x, int y)
{
	if (_sprite.getPosition().x <= x && x <= _sprite.getPosition().x + _texture.getSize().x &&
		_sprite.getPosition().y <= y && y <= _sprite.getPosition().y + _texture.getSize().y) return true;
	return false;
}
//turquoise
void Buttons::change_color()
{
	_sprite.setColor(sf::Color(102, 255, 153));
}
//purple
void Buttons::shine_color()
{
	_sprite.setColor(sf::Color(140, 102, 255));
}
//white
void Buttons::return_color()
{
	if (_sprite.getColor() != sf::Color::White) _sprite.setColor(sf::Color::White);
}

void Buttons::draw(sf::RenderWindow &window)
{
	window.draw(_sprite);
}

bool Buttons::is_shine()
{
	return _shine;
}

Menu::Menu()
{
	_is_menu = true;
	Buttons * b_exit = new Buttons("exit.png", 320, 400, true);
	Buttons * b_bubble = new Buttons("bubblesort.png", 320, 200, true);
	Buttons * b_std = new Buttons("stdsort.png", 320, 300, true);
	Buttons * b_left = new Buttons("left.png", 135, 50, true);
	Buttons * b_right = new Buttons("right.png", 508, 50, true);
	//b_pvp->_shine = true; b_pvp->shine_color();
	_buttons.push_back(b_exit);//0
	_buttons.push_back(b_bubble);//1
	_buttons.push_back(b_std);//2
	_buttons.push_back(b_left);//3
	_buttons.push_back(b_right);//4
}

Menu::~Menu()
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		delete _buttons[i];
	}
}

bool Menu::is_menu()
{
	return _is_menu;
}

void Menu::open()
{
	_is_menu = true;
	reset();
}

void Menu::close()
{
	_is_menu = false;
}

void Menu::draw(sf::RenderWindow &window, long long size)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (_buttons[i]->is_visible())
		{
			//da budet svet
			if (_buttons[i]->is_shine()) _buttons[i]->shine_color();
			_buttons[i]->draw(window);
		}
	}
	//put text
		//size of the game field
	sf::Font font;
	font.loadFromFile("calibri.ttf");
	std::string str;
	str = "size = " + std::to_string(size);
	sf::Text text(str, font, 40);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(230, 20);
	window.draw(text);
}

void Menu::change_colors(sf::Vector2f pos)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		//button 5 is "map's size". it;s not a button!!!
		if (_buttons[i]->contain(pos.x, pos.y) && i != 5)
		{
			_buttons[i]->change_color();
		}
		else
		{
			_buttons[i]->return_color();
		}
	}
}

void Menu::reset()
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (i <= 4)
			//new game //0
			//ext //1
			_buttons[i]->_visible = true;
		else
			//another are not visible
			_buttons[i]->_visible = false;
	}
}

void Menu::work(sf::Vector2f pos, sf::RenderWindow &window, long long &size, sort_type &type, Visualizer &vis)
{
	auto _comp = [&](Element a, Element b) {
		return Data::comp(a, b);
	};

	//button's functions
	auto to_do = [&](int n)
	{
		switch (n)
		{
			//exit
		case 0:
		{
			//game.~Game();
			window.close();

			break;
		}
		//bubble
		case 1:
		{
			shut_down = false;
			type = sort_type::bubble;
			_is_menu = false;

			Data d(10, 500, size);

			//Visualizer newVis;
			//vis = newVis;

			vis.setData(d);
			vis.setSize({ 800, 50 });
			vis.setPosition({ 0, 300 });

			Sortings s;
			vis.sort(s.getBubbleSort(), _comp);

			break;
		}
		//std
		case 2:
		{
			shut_down = false;
			type = sort_type::std;
			_is_menu = false;

			Data d(10, 500, size);

			vis.setData(d);
			vis.setSize({ 800, 50 });
			vis.setPosition({ 0, 300 });

			vis.sort(std::sort<decltype(d.begin()), decltype(_comp)>, _comp);

			break;
		}
		//left
		case 3:
		{
			if (size != 10) size /= 10;
			break;
		}
		//right
		case 4:
		{
			if (size != 100000) size *= 10;
			break;
		}
		}

	};
	for (int i = 0; i < _buttons.size(); i++)
	{
		//if we presssed correct button, let it work
		if (_buttons[i]->is_visible() && _buttons[i]->contain(pos.x, pos.y))
		{
			to_do(i);
			return;
		}
	}
}