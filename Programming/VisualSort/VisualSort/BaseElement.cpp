#include "BaseElement.h"

void swap(BaseElement &a, BaseElement &b)
{
	sf::Color temp = a._rect.getFillColor();
	a._rect.setFillColor(b._rect.getFillColor());
	b._rect.setFillColor(temp);
	std::swap(a._value, b._value);
}

BaseElement::BaseElement(float x, float y, float w, float h, long long value) : _rect(Point(w, h)), _value(value)
{
	_rect.setPosition(x, y);
	//_rect.setFillColor(color);
}


