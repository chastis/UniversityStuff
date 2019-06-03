#include "Visualizer.h"

Visualizer::Visualizer(Data & data) : _elements(data.getElements())
{ 
	//sorting.lock();
	//sorting.unlock();
	//temp_thread = 0;
}

void Visualizer::setData(Data & data)
{
	check_mutex();
	_elements = data.getElements();
}
void Visualizer::check_mutex()
{
	try
	{
		if (sorting.try_lock())
		{
			sorting.unlock();
		}
		else {
			std::cout << "third" << std::endl;
			temp_thread->detach();
			delete temp_thread;
			sorting.unlock();
		}
	}
	catch (...)
	{
		std::cout << "WTF3" << std::endl;
	}
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

void Visualizer::setWidth(float width)
{
	if (_elements.empty()) return;
	float new_el_w = width / _elements.size();
	for (auto& el : _elements) {
		el.setSize(sf::Vector2f(new_el_w, el.getSize().y));
	}
	setPosition(_elements.front().getPosition());
}

void Visualizer::setHeight(float heigth)
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

