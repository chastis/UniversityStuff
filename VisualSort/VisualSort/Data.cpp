#include "Data.h"


Data::Data(long long min, long long max, size_t size) : _min(min), _max(max), _data(size)
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<long long> uid(min, max);
	std::generate_n(_data.begin(), size, [&]() {return uid(dre); });
	//std::iota(_data.begin(), _data.end(), _min);
	generateElements();
}
Data::Data(const std::string & file)
{
	std::ifstream fin(file);
	long long temp;
	while (fin >> temp)
		_data.push_back(temp);
	fin.close();
	generateElements();
}
Data::Data(const std::vector<long long> & data) : _data(data)
{
	generateElements();
}

std::vector<sf::RectangleShape>& Data::getElements()
{
	return _elements;
}

std::vector<long long>::iterator Data::begin()
{
	return _data.begin();
}

std::vector<long long>::iterator Data::end()
{
	return _data.end();
}

std::vector<sf::RectangleShape>::iterator Data::el_begin()
{
	return _elements.begin();
}

std::vector<sf::RectangleShape>::iterator Data::el_end()
{
	return _elements.end();;
}

bool Data::comp(sf::RectangleShape a, sf::RectangleShape b)
{
	auto color_a = a.getFillColor();
	auto color_b = b.getFillColor();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	return color_a.g < color_b.g;
}

void Data::generateElements()
{
	_elements.clear();
	_elements.reserve(_data.size());
	for (auto d : _data) {
		sf::RectangleShape buff(sf::Vector2f(DEFAULT_EL_SIZE, DEFAULT_EL_SIZE));
		int green = 255 * (1 - (d - _min) / static_cast<float>(_max - _min));
		int red = 255 * (d - _min) / static_cast<float>(_max - _min);
		buff.setFillColor(sf::Color(red, green, 0));
		_elements.push_back(buff);
	}
}
