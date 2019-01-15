#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include "Object_Of_Image.h"
#include "Image.h"

using std::cout;
using std::cin;
using std::endl;

int main() {
	srand(time(0));

	Image race_image(100, 200);
	People car1_driver("Car's Driver", 10, 10);
	Car car_1("Racing Car", 40, 40);
	Lorry lorry("Lorry", 50, 50);
	People lorrys_driver("Lorry's Driver", 15, 20);
	Car car_2("NoRacing Car", 50, 40);
	Wheel lorrys_wheel("Lorry's wheel", 20, 20);
	Shell lorrys_shell("Lorry's shell", 40, 40);
	Wheel cars2_wheel("NoRacing Car's wheel", 10, 10);
	Shell cars2_shell("NoRacing Car's shell", 40, 40);
	lorry.push_part(&lorrys_wheel);
	lorry.push_part(&lorrys_shell);
	car_2.push_part(&cars2_shell);
	car_2.push_part(&cars2_shell);
	car1_driver.neighbour().push_back(&car_1);
	car_1.neighbour().push_back(&car1_driver);
	lorry.neighbour().push_back(&lorrys_driver);
	lorrys_driver.neighbour().push_back(&lorry);
	lorry.neighbour().push_back(&car_2);
	car_2.neighbour().push_back(&lorry);
	race_image.existing_objects().push_back(&lorry);
	race_image.existing_objects().push_back(&car1_driver);
	race_image.existing_objects().push_back(&car_1);
	race_image.existing_objects().push_back(&car_2);
	race_image.existing_objects().push_back(&lorrys_driver);

	Image parking_image(200, 200);
	Car machine1("machine1", 50, 50);
	Car machine2("machine2", 50, 50);
	Lorry track1("Lorry1", 50, 50);
	Lorry track2("Lorry2", 50, 50);
	machine1.neighbour().push_back(&machine2);
	machine2.neighbour().push_back(&machine1);
	track1.neighbour().push_back(&track2);
	track2.neighbour().push_back(&track1);
	parking_image.existing_objects().push_back(&machine1);
	parking_image.existing_objects().push_back(&machine2);
	parking_image.existing_objects().push_back(&track2);
	parking_image.existing_objects().push_back(&track1);

	std::vector<Image> images;
	std::vector<Object * > objects;
	std::tm low, up;
	low.tm_hour = 0;
	low.tm_min = 0;
	low.tm_sec = 0;
	up.tm_hour = 24;
	up.tm_min = 60;
	up.tm_sec = 60;

	race_image.recognazing();
	parking_image.recognazing();

	images.push_back(race_image);
	images.push_back(parking_image);
	objects.push_back(&car1_driver);
	objects.push_back(&car_1);
	objects.push_back(&lorry);
	objects.push_back(&lorrys_driver);
	objects.push_back(&car_2);
	objects.push_back(&lorrys_wheel);
	objects.push_back(&lorrys_shell);
	objects.push_back(&cars2_shell);
	objects.push_back(&cars2_wheel);
	objects.push_back(&machine1);
	objects.push_back(&machine2);
	objects.push_back(&track1);
	objects.push_back(&track2);

	sort_by_time(images);

	size_t count_of_unknown = solved_four_values(images, objects, low, up);


	//UI

	while (true)
	{
		cout << "Choose option!" << endl;
		cout << "1 : get information about object" << endl;
		cout << "2 : get information about images" << endl;
		cout << "3 : get count of unknown objects" << endl;
		cout << "4 : exit" << endl;
		int option;
		cin >> option;
		if (option == 1)
		{
			cout << "List of Objects:" << endl << endl;
			int n = 0;
			for (auto now : objects)
				cout << "[" << n++ << "] " << now << endl;

			cout << endl << "Choose Object!" << endl;
			cin >> n;
			if (n < 0 || n >= objects.size())
			{
				cout << "ERROR 404 ELEMENT NOT FOUND " << endl;
				continue;
			}
			cout << "Details: " << endl;
			cout << endl << objects[n]->name() << endl;
			cout << "Positive: " << objects[n]->positive() << endl;
			cout << "Negative: " << objects[n]->negative() << endl;
			cout << "False positive: " << objects[n]->false_positive() << endl;
			cout << "False negative: " << objects[n]->false_negative() << endl;
		}
		else if (option == 2)
		{
			cout << "List of images:" << endl << endl;
			int n = 0;
			for (auto now : images)
			{
				cout << "[" << n++ << "] " << "Image " << now.id() << ", created at (" << now.creation_time().tm_hour << ";" << now.creation_time().tm_min << ";" << now.creation_time().tm_sec << ")" << endl;
			}
			cout << endl << "Choose Image!" << endl;

			cin >> n;
			if (n < 0 || n >= images.size())
			{
				cout << "ERROR 404 ELEMENT NOT FOUND " << endl;
				continue;
			}
			cout << "Details: " << endl;
			cout << endl << "Image " << images[n].id() << endl;
			cout << "Existing Objects:" << endl;
			for (auto now : images[n].existing_objects())
			{
				cout << now << endl;
			}
			cout << endl << "Recognized Objects:" << endl;
			for (auto now : images[n].recognized_objects())
			{
				cout << now << endl;
			}

		}
		else if (option == 3)
		{
			cout << endl << "count Unknown objects = " << count_of_unknown << endl;
		}
		else if (option == 4)
		{
			break;
		}
		else
		{
			cout << "SORRY! I don't know what I have to DO!" << endl;
		}
		cout << endl << endl << endl;
		if (cin.bad() || cin.fail()) {
			if (cin.eof()) cin.clear();
			else
			{
				while (cin.get() != '\n')
					cin.clear();
			}
			cout << "SORRY! I don't know what I have to DO!" << endl;
		}
	}


	cout << "That's all Folks!" << endl;
	_getch();
	return 0;
}