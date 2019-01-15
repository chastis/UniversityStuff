#ifndef OBJECT_OF_IMAGE_H
#define OBJECT_OF_IMAGE_H

#include <string>
#include <vector>
//#include "Image.h"

//клас існуючих об'єктів
enum class objects {
	//людина
	people,
	//машина
	car,
	//корпус машини
	shell,
	//колесо машини
	wheel,
	//дерево
	tree,
	//стовбур дерева
	trunk,
	//листя дерева
	leaves,
	//невідомий тип
	unknown,
	//тип у стандартного об'єкта
	none,
	//вантажівка
	lorry,
	//кущ
	bush
};

//для виводу класу-перечислення objects
std::ostream& operator << (std::ostream& os, const objects& obj);

//батьківський клас Об'єкт
class Object {
	friend class Image;
	friend size_t solved_four_values(std::vector<Image>  &images, std::vector<Object *>  &objects, std::tm low, std::tm up);
	friend std::ostream& operator << (std::ostream& os, const Object* obj);
public:
	explicit Object(std::string _name = "", size_t _length = 0, size_t _width = 0);
	~Object();
	//повертає ім'я
	std::string name();
	//повертає довжину
	size_t length();
	//повертає ширину
	size_t width();
	//повертає тип
	objects type();
	//повертає об'єктів-сусідів
	std::vector<Object *> &neighbour();
	//повертає об'єкти-частки
	std::vector<Object *> part();
	//Добавляет объект-частичку
	void push_part(Object *);
	//повертає схожі об'єкти
	std::vector<objects> &similar();
	//возвращает площадь объектов-частичек поделенную на площадь объекта
	//или наоборот, если вторая больше первой
	double part_area();

	//
	//объект есть на картинке и был распознан
	size_t positive();
	//объекта нету, но он и небыл распознан
	size_t negative();
	//объекта нет, но он был распознан
	size_t false_positive();
	//объект есть, но не был распознан
	size_t false_negative();
private:
protected:
	//ім'я
	std::string _name;
	//довжина
	size_t _length;
	//ширина
	size_t _width;
	//тип
	objects _type;
	//об'єкти-сусіди
	std::vector<Object *> _neighbour;
	//об'єкти-частки
	std::vector<Object *> _part;
	//площа объектов-частичек
	size_t _part_area;
	//схожі об'єкти
	std::vector<objects> _similar;

	//данные полученные из изображений
	//
	//объект есть на картинке и был распознан
	size_t _positive;
	//объекта нету, но он и небыл распознан
	size_t _negative;
	//объекта нет, но он был распознан
	size_t _false_positive;
	//объект есть, но не был распознан
	size_t _false_negative;
};

//для виводу класу Object
std::ostream& operator << (std::ostream& os, const Object* obj);

//клас Людини
class People : public Object {
public:
	enum positions
	{
		seat, stand, run, lay
	};
	explicit People(std::string _name = "", size_t _length = 0, size_t _width = 0);
	~People();
	positions position();
private:
	positions _position;
};

//клас Машини
class Car : public Object {
public:
	enum positions
	{
		stand, ride
	};
	explicit Car(std::string _name, size_t _length, size_t _width);
	~Car();
	positions position();
	void set_position(positions pos);
private:
	positions _position;
};

//клас Корпуса машини
class Shell : public Object {
public:
	enum positions
	{
		normal, broken, open_door, without_roof
	};
	explicit Shell(std::string _name, size_t _length, size_t _width);
	~Shell();
	positions position();
private:
	positions _position;


};

//клас Колеса машини
class Wheel : public Object {
public:
	enum positions
	{
		rotate, stand
	};
	explicit Wheel(std::string _name, size_t _length, size_t _width);
	~Wheel();
	positions position();
private:
	positions _position;

};

//клас Unknown
class Unknown : public Object {
public:
	enum positions
	{
		unknown
	};
	explicit Unknown();
	~Unknown();
	positions position();

private:
	positions _position;

};

//клас Вантажівки
class Lorry : public Object {
public:
	enum positions
	{
		stand, ride
	};
	explicit Lorry(std::string _name, size_t _length, size_t _width);
	~Lorry();
	positions position();

private:
	positions _position;

};

//
class Universal : public Object {
private:
	enum positions
	{
		one, two, three, four, five, six, seven, eight, nine, ten
	} _position;
public:
	explicit Universal()
	{
	};
	explicit Universal(Object * temp)
	{
		//_position = temp->_position;
	};
	~Universal() {};
	positions position()
	{
		return _position;
	}
};
#endif // !OBJECT_OF_IMAGE_H
