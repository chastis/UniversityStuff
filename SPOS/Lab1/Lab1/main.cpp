//#include <iostream>
//#include <thread>
//#include <windows.h>
//#include <stdio.h>
//#include <tchar.h>
//#include <chrono>
//#include <future>
//
//void cleanUpCin()
//{
//	std::cout << "Incorrect input" << std::endl;
//	std::cin.clear();
//	while (std::cin.get() != '\n')
//	{
//		std::cin.ignore();
//	}
//}
//
//template <class In, class Out>
//void f(In x, Out* y)
//{
//	*y = x;
//}
//
//template <class In, class Out>
//void g(In x, Out* y)
//{
//	*y = x;
//}
//
//class TimeManager
//{
//public:
//	void start()
//	{
//		startPoint = std::chrono::high_resolution_clock::now();
//	}
//	float getTime() const
//	{
//		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startPoint).count();
//	}
//	bool isTimePassed(const float milliseconds) const
//	{
//		return getTime() >= milliseconds;
//	}
//private:
//	std::chrono::high_resolution_clock::time_point startPoint;
//};
//
//int main(int argc, TCHAR* argv[])
//{
//
//
//	while (true)
//	{
//		std::cout << "Please, choose option!" << std::endl;
//		std::cout << "[1] - f() AND g()" << std::endl;
//		std::cout << "[2] - f() OR g()" << std::endl;
//		std::cout << "[3] - MIN ( f(), g() )" << std::endl;
//		std::cout << "[4] - f() * g()" << std::endl;
//		std::cout << "[5] - Exit" << std::endl;
//		int operationNum;
//		while (!(std::cin >> operationNum) || operationNum < 1 || operationNum>5)
//		{
//			cleanUpCin();
//		}
//		switch (operationNum)
//		{
//			case 1:
//			{
//				STARTUPINFO si;
//				PROCESS_INFORMATION pi;
//
//				ZeroMemory(&si, sizeof(si));
//				si.cb = sizeof(si);
//				ZeroMemory(&pi, sizeof(pi));
//
//				char name[] = "TEST.exe 11";
//
//				if (!CreateProcess(NULL,   // No module name (use command line)
//					name,        // Command line
//					NULL,           // Process handle not inheritable
//					NULL,           // Thread handle not inheritable
//					FALSE,          // Set handle inheritance to FALSE
//					0,              // No creation flags
//					NULL,           // Use parent's environment block
//					NULL,           // Use parent's starting directory 
//					&si,            // Pointer to STARTUPINFO structure
//					&pi)           // Pointer to PROCESS_INFORMATION structure
//					)
//				{
//					printf("CreateProcess failed (%d).\n", GetLastError());
//					return 1;
//				}
//
//					CreateThread()
//
//				// Wait until child process exits.
//				/*
//				auto f_proc = std::async(std::launch::async,
//					[&]()
//					{
//						return WaitForSingleObject(pi.hProcess, INFINITE);
//					}
//				);
//
//				while ()*/
//
//				//WaitForSingleObject(pi.hProcess, INFINITE);
//
//				// Close process and thread handles. 
//				CloseHandle(pi.hProcess);
//				CloseHandle(pi.hThread);
//				break;
//			}
//			case 2:
//			{
//
//				break;
//			}
//			case 3:
//			{
//
//				break;
//			}
//			case 4:
//			{
//
//				break;
//			}
//			case 5:
//			{
//				return 0;
//			}
//			default:
//			{
//				std::cout << "You broke my program..." << std::endl;
//			}
//		}
//	}
//}

#include <windows.h>

struct MyData
{
	int a;
	double b;
};

DWORD func(LPVOID data)
{
	auto myData = static_cast<MyData*>(data);
	myData->a = 5;
	return 0;
}


int main()
{
	MyData b{ 1, 2.f };
	func(&b);
	return b.a;

}