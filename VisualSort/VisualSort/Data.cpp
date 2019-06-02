#include "Data.h"


Data::Data(long long min, long long max, size_t size) : _min(min), _max(max), _elements(size)
{ 
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<long long> uid(min, max);
	std::generate_n(_elements.begin(), size, [&]() {
		Element buff;
		buff.setValue(uid(dre));
		return buff;
	});
	//std::iota(_data.begin(), _data.end(), _min);
	generateElements();
}
Data::Data(const std::string & file)
{
	std::ifstream fin(file);
	long long temp;
	while (fin >> temp) {
		Element t(sf::Vector2f(DEFAULT_EL_SIZE, DEFAULT_EL_SIZE));
		t.setValue(temp);
		_elements.push_back(t);
	}
	fin.close();
	generateElements();
}
Data::Data(const std::vector<long long> & data)
{
	_elements.clear();
	_elements.reserve(data.size());
	for (auto d : data) {
		Element buff;
		buff.setValue(d);
		_elements.push_back(buff);
	}
}

std::vector<Element>& Data::getElements()
{
	// TODO: insert return statement here
	return _elements;
}

bool Data::comp(Element a, Element b)
{
	/*auto color_a = a.getColor();
	auto color_b = b.getColor();
	s1td::this_thread::sleep_for(std::chrono::microseconds(1));*/
	//std::this_thread::sleep_for(std::chrono::microseconds(2));
	return a.getValue() < b.getValue();
}

std::vector<Element>::iterator Data::begin()
{
	return _elements.begin();
}

std::vector<Element>::iterator Data::end()
{
	return _elements.end();
}

void Data::generateElements()
{
	for (auto& el : _elements) {

		auto d = el.getValue();
		int h = static_cast<int>((d - _min) / static_cast<float>(_max - _min) * 256 * 6);
		int x = h % 0x100;

		int r = 0, g = 0, b = 0;
		switch (h / 256)
		{
		case 0: r = 255; g = x;       break;
		case 1: g = 255; r = 255 - x; break;
		case 2: g = 255; b = x;       break;
		case 3: b = 255; g = 255 -  x; break;
		case 4: b = 255; r = x;       break;
		case 5: r = 255; b = 255 - x; break;
		}
		el.setColor(sf::Color(r, g, b));
		/*Element buff(sf::Vector2f(DEFAULT_EL_SIZE, DEFAULT_EL_SIZE));
		int green = 255 * (1 - (d - _min) / static_cast<float>(_max - _min));
		int red = 255 * (d - _min) / static_cast<float>(_max - _min);
		int blue = 255 *(d - _min) / static_cast<float>(_max - _min);
		buff.setColor(sf::Color(red, green, 0));
		_elements.push_back(buff);*/
	}
}
