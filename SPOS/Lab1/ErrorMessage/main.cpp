#include <iostream>
#include <thread>
#include <chrono>

int main()
{
	for (int32_t i = 60; i--; i >= 0)
	{
		system("cls");
		std::cout << "Do you want to stop calculating?" << std::endl;
		std::cout << "y/n for yes/no" << std::endl;
		std::cout << "Automatic cancel in " << i << " sec!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return 42;
}