#include <iostream>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <tchar.h>
#include <chrono>
#include <future>
#include <sstream>

namespace MyNamespace
{
	/* global variables */

	uint32_t DefaultSize = 100;
	uint32_t ExitParam = 0;

	/* methods */

	void cleanUpCin()
	{
		std::cout << "Incorrect input" << std::endl;
		std::cin.clear();
		while (std::cin.get() != '\n')
		{
			std::cin.ignore();
		}
	}

	class TimeManager
	{
	public:
		void start()
		{
			startPoint = std::chrono::high_resolution_clock::now();
		}
		float getTime() const
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startPoint).count();
		}
		bool isTimePassed(const float milliseconds) const
		{
			return getTime() >= milliseconds;
		}
	private:
		std::chrono::high_resolution_clock::time_point startPoint;
	};

	bool CreateProcess(char* name, LPSTARTUPINFOA startupInfo, LPPROCESS_INFORMATION processInfo)
	{
		return CreateProcess(
			NULL,            // No module name (use command line)
			name,                          // Command line
			NULL,         // Process handle not inheritable
			NULL,         // Thread handle not inheritable
			FALSE,         // Set handle inheritance to FALSE
			0,            // No creation flags
			NULL,          // Use parent's environment block
			NULL,     // Use parent's starting directory 
			startupInfo,             // Pointer to STARTUPINFO structure
			processInfo);           // Pointer to PROCESS_INFORMATION structure
	}
}
 

int main(int argc, TCHAR* argv[])
{


	while (true)
	{
		system("cls");
		std::cout << "Please, choose option!" << std::endl;
		std::cout << "[1] - Start" << std::endl;
		std::cout << "[2] - Exit" << std::endl;
		int operationNum;
		while (!(std::cin >> operationNum) || operationNum < 1 || operationNum>5)
		{
			MyNamespace::cleanUpCin();
		}
		switch (operationNum)
		{
		case 1:
		{
			STARTUPINFO siG;
			PROCESS_INFORMATION piG;

			ZeroMemory(&siG, sizeof(siG));
			siG.cb = sizeof(siG);
			ZeroMemory(&piG, sizeof(piG));

			char* processName = new char[MyNamespace::DefaultSize];
			const DWORD thisThreadId = GetCurrentThreadId();
			std::cout << "this thread = " << thisThreadId << std::endl;

			std::string stringName = "FunctionG.exe " + std::to_string(thisThreadId);
			strcpy_s(processName, MyNamespace::DefaultSize, stringName.c_str());

			if (!MyNamespace::CreateProcessA(processName, &siG, &piG))
			{
				std::cout << "CreateProcess G failed" << std::endl;
				return 1;
			}

			STARTUPINFO siF;
			PROCESS_INFORMATION piF;

			ZeroMemory(&siF, sizeof(siF));
			siF.cb = sizeof(siF);
			ZeroMemory(&piF, sizeof(piF));

			stringName = "FunctionF.exe " + std::to_string(thisThreadId);
			strcpy_s(processName, MyNamespace::DefaultSize, stringName.c_str());

			if (!MyNamespace::CreateProcessA(processName, &siF, &piF))
			{
				std::cout << "CreateProcess F failed" << std::endl;
				return 1;
			}
			MSG msg;
			std::cout << "start to getting message..." << std::endl;
			// some strange architecture
			std::pair<bool, UINT> a{ false, 0 }, b{false, 0};
			while (!a.first||!b.first)
			{
				const BOOL bRet = GetMessage(&msg, NULL, 0,UINT32_MAX);
				if (bRet)
				{
					const UINT Message = msg.message - msg.wParam;
					std::cout << "NEW MESSAGE!!!! " << Message << std::endl;
					if (!a.first)
					{
						a.first = true;
						a.second = Message;
					}
					else if (!b.first)
					{
						b.first = true;
						b.second = Message;
					}
					if (Message == MyNamespace::ExitParam)
					{
						TerminateProcess(piF.hProcess, 0);
						TerminateProcess(piG.hProcess, 0);
						std::cout << "Program has done, because one of params is " << MyNamespace::ExitParam << std::endl;
						break;
					}				
				}
			}


			CloseHandle(piF.hProcess);
			CloseHandle(piG.hProcess);
			std::cout << "Program finished successfully!" << std::endl;
			std::cout << "Output is " << a.second << " and " << b.second << std::endl;
			std::cout << "Enter smth to continue..." << std::endl;
			_getch();
			break;
		}
		case 2:
		{
			return 0;
		}
		default:
		{
			std::cout << "You broke my program..." << std::endl;
			MyNamespace::cleanUpCin();
		}
		}
	}
}
