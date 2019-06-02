#ifndef SORTINGS_H
#define SORTINGS_H
#include"helpers.h"
#include"Element.h"

class Sortings
{
public:
	Sortings();
	~Sortings();
	//template <class T>
	std::function<void(std::vector<Element>::iterator , std::vector<Element>::iterator , std::function<bool(Element, Element)>)> getBubbleSort();
};
#endif
