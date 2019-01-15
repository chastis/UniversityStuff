#ifndef IMAGE_H
#define IMAGE_H

#include <ctime>
#include <chrono>
#include <vector>
#include "My_Data.h"
#include "Object_Of_Image.h"

//Загальний клас зображення
class Image {
public:
	Image(size_t _length = 1, size_t _width = 1);
	~Image();
	//повертає час створення
	std::tm creation_time();
	//повертає довжину
	size_t length();
	//повертає ширину
	size_t width();
	//повертає ідентифікатор
	size_t id();
	//повертає об'єкти на зображенні
	std::vector<Object *> &existing_objects();
	//повертає розпознані об'єкти
	std::vector<Object *> recognized_objects();
	//распознование
	void recognazing();
	//возвращает распознанный объект, или неизвестный объект
	Object * return_recognized_object(Object *);
private:
	//унікальний ідентифікатор
	size_t _id;
	//час створення
	//std::chrono::steady_clock::time_point _creation_time;
	std::tm _creation_time;
	//довжина
	size_t _length;
	//ширина
	size_t _width;

	//агрегирование
	//об'єкти на зображенні
	std::vector<Object *> _existing_objects;
	//розпознані об'єкти
	std::vector<Object *> _recognized_objects;
};

//функція для виводу часу
std::ostream& operator << (std::ostream& os, const std::tm& obj);

//сортировка изображений по времени
void sort_by_time(std::vector<Image>  &images);

//Реалізувати алгоритм, що для заданого періоду часу та списку об’єктів розраховує
//для кожного об’єкта описані 4 значення,
//а також загальну кількість розпізнаних «невідомих об’єктів».
//возвращает количество неопознанных объектов
size_t solved_four_values(std::vector<Image>  &images, std::vector<Object *>  &objects, std::tm low, std::tm up);
#endif // !IMAGE_H
