#ifndef DATA_H
#define DATA_H

#include "helpers.h"
#include "BaseElement.h"

class Data
{
public:
	Data(long long, long long, size_t);
	Data(const std::string &);
	Data(const std::vector<long long> &);
		
	std::vector<sf::RectangleShape>& getElements();

	std::vector<long long>::iterator begin();
	std::vector<long long>::iterator end();
	std::vector<sf::RectangleShape>::iterator el_begin();
	std::vector<sf::RectangleShape>::iterator el_end();

	~Data() = default;

	static bool comp(sf::RectangleShape, sf::RectangleShape);

private:
	long long _min;
	long long _max;
	std::vector<long long> _data;
	std::vector<sf::RectangleShape> _elements;
	void generateElements();
};

#endif // !DATA_H
