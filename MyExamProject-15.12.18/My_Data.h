#ifndef MY_DATA_H
#define MY_DATA_H

#include "Object_Of_Image.h"

//global namespace
namespace gl {

	//для унікальності айді
	static size_t current_id = 0;
	//похибка для об'єктів частин
	static const double calc_error = 0.1;

	//дальше шансы, чем ниже переменная - тем больше шанс!

	//шанс повернути схожий об'єкт
	static const double chance_similar = 50;
	//шанс повернути список частин
	static const double chance_part = 50;
	//шанс повернути один об'єкт замість сусідів
	static const double chance_neighbour = 50;
	//шанс повернути невідомий об'єкт
	static const double chance_unknown = 25;
	//невідомий об'єкт
	static Unknown * unknown_object = new Unknown;

}

#endif // !MY_DATA_H
