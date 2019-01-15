#include <time.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iostream>
#include "Object_Of_Image.h"


//output objects
std::ostream& operator << (std::ostream& os, const objects& obj)
{
	os << static_cast<std::underlying_type<objects>::type>(obj);
	return os;
}

//output Object
std::ostream& operator << (std::ostream& os, const Object* obj)
{
	os << "Object: " << obj->_name;
	//os << "Type: " << obj._type << std::endl;
	return os;
}

//Object

Object::Object(std::string _name, size_t _length, size_t _width)
	: _name(_name), _length(_length), _width(_width)
{
	_type = objects::none;
	_similar.push_back(objects::unknown);
	_positive = 0;
	_negative = 0;
	_false_negative = 0;
	_false_positive = 0;
}

Object::~Object()
{

}

size_t Object::length()
{
	return _length;
}

size_t Object::width()
{
	return _width;
}

std::string Object::name()
{
	return _name;
}

objects Object::type()
{
	return _type;
}

std::vector<Object *> &Object::neighbour()
{
	return _neighbour;
}

std::vector<Object *> Object::part()
{
	return _part;
}

std::vector<objects> &Object::similar()
{
	return _similar;
}

void Object::push_part(Object * temp) {
	_part_area += temp->length()*temp->width();
	_part.push_back(temp);
}

double Object::part_area()
{
	return (double)std::min(_part_area, _length*_width) / std::max(_part_area, _length*_width);
}

size_t Object::positive()
{
	return _positive;
}

size_t Object::negative()
{
	return _negative;
}

size_t Object::false_positive()
{
	return _false_positive;
}

size_t Object::false_negative()
{
	return _false_negative;
}

//People

People::People(std::string _name, size_t _length, size_t _width) : Object::Object(_name, _length, _width)
{
	_type = objects::people;
	_position = positions::stand;
}

People::~People()
{

}

People::positions People::position()
{
	return _position;
}

//Car

Car::Car(std::string _name, size_t _length, size_t _width) : Object::Object(_name, _length, _width)
{
	_type = objects::car;
	_position = positions::stand;
	_similar.push_back(objects::lorry);
}

Car::~Car()
{

}

Car::positions Car::position()
{
	return _position;
}

void Car::set_position(positions pos)
{
	_position = pos;
}

//Shell

Shell::Shell(std::string _name, size_t _length, size_t _width) : Object::Object(_name, _length, _width)
{
	_type = objects::shell;
	_position = positions::normal;
}

Shell::~Shell()
{

}

Shell::positions Shell::position()
{
	return _position;
}

//Wheel

Wheel::Wheel(std::string _name, size_t _length, size_t _width) : Object::Object(_name, _length, _width)
{
	_type = objects::wheel;
	_position = positions::stand;
}

Wheel::~Wheel()
{

}

Wheel::positions Wheel::position()
{
	return _position;
}

//Unknown

Unknown::Unknown()
{
	_name = "unknown";
	_type = objects::unknown;
	_position = positions::unknown;
	_length = 0;
	_width = 0;
	_similar.push_back(objects::unknown);
}

Unknown::~Unknown()
{

}

Unknown::positions Unknown::position()
{
	return _position;
}

//Lorry

Lorry::Lorry(std::string _name, size_t _length, size_t _width) : Object::Object(_name, _length, _width)
{
	_type = objects::lorry;
	_position = positions::stand;
	_similar.push_back(objects::car);
}

Lorry::~Lorry()
{

}

Lorry::positions Lorry::position()
{
	return _position;
}
