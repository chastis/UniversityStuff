#ifndef DATA_H
#define DATA_H

#include "helpers.h"
#include "Element.h"

class Data
{
public:
	Data(long long, long long, size_t);
	Data(const std::string &);
	Data(const std::vector<long long> &);
	~Data() = default;

	std::vector<Element>& getElements();

	static bool comp(Element, Element);

	std::vector<Element>::iterator begin();
	std::vector<Element>::iterator end();

private:
	long long _min;
	long long _max;
	//std::vector<long long> _data;
	std::vector<Element> _elements;
	void generateElements();
};

#endif // !DATA_H
