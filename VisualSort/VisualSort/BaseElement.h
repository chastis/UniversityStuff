#ifndef BASEELEMENT_H
#define BASEELEMENT_H

#include "helpers.h"

class BaseElement
{
public:
	friend void swap(BaseElement &, BaseElement &);
	BaseElement(float x, float y, float w, float h, long long value);
	void gene
	virtual ~BaseElement() = default;
private:
	sf::RectangleShape _rect;
	long long _value;
};


void swap(BaseElement &a, BaseElement &b);
#endif // !BaseElement
