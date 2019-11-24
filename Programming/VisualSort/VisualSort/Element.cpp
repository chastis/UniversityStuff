#include "Element.h"

Element::Element() : _shape({ 0, 0 }) {}

Element::Element(sf::Vector2f size) : _shape(size) {}

void Element::setPosition(const sf::Vector2f& pos)
{
	_shape.setPosition(pos);
}

void Element::setSize(const sf::Vector2f& size)
{
	_shape.setSize(size);
}

void Element::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_shape, states);
}

void Element::setColor(sf::Color clr)
{
	_shape.setFillColor(clr);
}

sf::Color Element::getColor() const
{
	return _shape.getFillColor();
}

long long Element::getValue() const
{
	return _value;
}

void Element::setValue(long long value)
{
	_value = value;
}

Element & Element::operator=(const Element & rhs)
{
	// TODO: insert return statement here
	_shape.setFillColor(rhs._shape.getFillColor());
	_value = rhs._value;
	return *this;
}

sf::Vector2f Element::getPosition() const
{
	return _shape.getPosition();
}

sf::Vector2f Element::getSize() const
{
	return _shape.getSize();
}
