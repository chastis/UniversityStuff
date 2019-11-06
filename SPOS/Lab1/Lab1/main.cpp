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
	enum class InputKey
	{
		Yes,
		No,
		None
	};

	/* global variables */

	uint32_t DefaultSize = 100;
	uint32_t ExitParam = 0;
	uint32_t SecondsToTryTerminate = 10;
	bool bEscapeRequest = false;
	bool bIsErrorMessageCreated = false;
	InputKey inputKey = InputKey::None;

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

	bool CreateProcess(char* name, LPSTARTUPINFOA startupInfo, LPPROCESS_INFORMATION processInfo, DWORD flag = 0)
	{
		return CreateProcess(
			NULL,            // No module name (use command line)
			name,                          // Command line
			NULL,         // Process handle not inheritable
			NULL,         // Thread handle not inheritable
			FALSE,        // Set handle inheritance to FALSE
			flag,            // No creation flags
			NULL,          // Use parent's environment block
			NULL,     // Use parent's starting directory 
			startupInfo,             // Pointer to STARTUPINFO structure
			processInfo);           // Pointer to PROCESS_INFORMATION structure
	}
}
 

int main(int argc, TCHAR* argv[])
{
	auto f_proc = std::async(std::launch::async, []()
	{
			while (true)
			{
				if (GetAsyncKeyState(VK_ESCAPE) == -32767)
					MyNamespace::bEscapeRequest = true;
				if (GetAsyncKeyState(0x59) == -32767)
					MyNamespace::inputKey = MyNamespace::InputKey::Yes;
				if (GetAsyncKeyState(0x4E) == -32767)
					MyNamespace::inputKey = MyNamespace::InputKey::No;
			}
	});
	

	while (true)
	{
		MyNamespace::inputKey = MyNamespace::InputKey::None;
		MyNamespace::bEscapeRequest = false;
		MyNamespace::bIsErrorMessageCreated = false;

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


			STARTUPINFO siError;
			PROCESS_INFORMATION piError;
			DWORD errorExitCode = 0;
			// some strange architecture
			std::pair<bool, UINT> a{ false, 0 }, b{false, 0};
			while (!a.first||!b.first)
			{
				if (MyNamespace::bEscapeRequest)
				{
					if (!MyNamespace::bIsErrorMessageCreated)
					{
						ZeroMemory(&siError, sizeof(siError));
						siError.cb = sizeof(siError);
						ZeroMemory(&piError, sizeof(piError));

						char errorProcessName[] = "ErrorMessage";
						if (!MyNamespace::CreateProcessA(errorProcessName, &siError, &piError, CREATE_NEW_CONSOLE))
						{
							std::cout << "Create ErrorProcess failed" << std::endl;
						}
						MyNamespace::bIsErrorMessageCreated = true;
					}
					MyNamespace::bEscapeRequest = false;
				}
				if (MyNamespace::bIsErrorMessageCreated)
				{
					GetExitCodeProcess(piError.hProcess, &errorExitCode);
					if (MyNamespace::inputKey == MyNamespace::InputKey::Yes || errorExitCode!=STILL_ACTIVE)
					{
						std::cout << "Calculation was stopped" << std::endl;
						MyNamespace::bIsErrorMessageCreated = false;
						TerminateProcess(piF.hProcess, 0);
						TerminateProcess(piG.hProcess, 0);
						TerminateProcess(piError.hProcess, 0);
						break;
					}
					else if (MyNamespace::inputKey == MyNamespace::InputKey::No)
					{
						MyNamespace::bIsErrorMessageCreated = false;
						TerminateProcess(piError.hProcess, 0);
					}
					MyNamespace::inputKey = MyNamespace::InputKey::None;
				}
				
				const BOOL bRet = PeekMessage(&msg, NULL, 0, UINT32_MAX, PM_REMOVE);
				//const BOOL bRet = GetMessage(&msg, NULL, 0,UINT32_MAX);
				if (bRet)
				{
					const UINT Message = msg.message - msg.wParam;
					std::cout << "Got new Message! " << Message << std::endl;
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

			TerminateProcess(piError.hProcess, 0);
			CloseHandle(piF.hProcess);
			CloseHandle(piG.hProcess);
			CloseHandle(piError.hProcess);
			std::cout << "Program finished successfully!" << std::endl;
			std::cout << "Output is " << (a.first ? std::to_string(a.second) : "a wasn't calculated") << " and " << (b.first ? std::to_string(b.second) : "b wasn't calculated") << std::endl;
			std::cout << "Enter smth to continue..." << std::endl;
			std::cin.get();
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
