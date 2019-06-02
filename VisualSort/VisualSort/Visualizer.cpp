#include "Visualizer.h"

Visualizer::Visualizer(Data & data) : _data(data), _elements(data.getElements()), pos(0, 0)
{ 
	//setPosition({ 0,0 }); 
}

void Visualizer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto& el : _elements)
	{
		auto temp = el;
		target.draw(temp, states);
	}
}

void Visualizer::setPosition(const sf::Vector2f & pos)
{
	this->pos = pos;
	if (_elements.empty()) return;
	_elements.front().setPosition(pos);
	for (size_t i = 1; i < _elements.size(); i++)
	{
		//auto a = _elements[i - 1].getPosition();
		auto b = sf::Vector2f(_elements[i - 1].getSize().x * i, 0);
		_elements[i].setPosition(pos + b);
	}
}

const sf::Vector2f Visualizer::getPosition() const
{
	if (_elements.empty()) return { 0, 0 };
	else return _elements.front().getPosition();
}

void Visualizer::setWidth(size_t width)
{
	if (_elements.empty()) return;
	size_t new_el_w = width / _elements.size();
	for (auto& el : _elements) {
		el.setSize(sf::Vector2f(new_el_w, el.getSize().y));
	}
	setPosition(_elements.front().getPosition());
}

void Visualizer::setHeight(size_t heigth)
{
	if (_elements.empty()) return;
	for (auto& el : _elements) {
		el.setSize(sf::Vector2f(el.getSize().x, heigth));
	}
	setPosition(_elements.front().getPosition());
}

void Visualizer::setSize(sf::Vector2f size)
{
	setHeight(size.y);
	setWidth(size.x);
}

const sf::Vector2f Visualizer::getSize()
{
	if (_elements.empty()) return { 0, 0 };
	auto el_size = _elements.front().getSize();
	return { _elements.size() * el_size.x, el_size.y };
}

void Visualizer::sort()
{
	std::sort(_elements.begin(), _elements.end(), Data::comp);
	
}

std::vector<sf::RectangleShape>::iterator& Visualizer::el_begin()
{
	return _elements.begin();
}

std::vector<sf::RectangleShape>::iterator& Visualizer::el_end()
{
	return _elements.end();
}

void Visualizer::print()
{
	for (auto now : _elements)
	{
		sf::Color temp = now.getFillColor();
		std::cout << temp.g << " ";
	}
	std::cout << std::endl;
}
