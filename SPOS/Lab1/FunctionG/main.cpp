#include <iostream>
#include <windows.h>
#include <thread>
#include "demofuncs"

int main(int argc, TCHAR* argv[])
{
	if (argc < 2)
	{
		std::cout << "process G broken " << std::endl;
		return 1;
	}
	const DWORD processID = std::atoi(argv[1]);
	const int32_t x = std::atoi(argv[2]);

	// here go function

	uint32_t answer = spos::lab1::demo::g_func<spos::lab1::demo::INT>(x);
	uint32_t wParam = 0;
	if (answer<=WM_USER)
	{
		wParam = WM_USER + 1;
		answer += wParam;
	}
	const BOOL success = PostThreadMessageW(processID, answer, wParam, 0);
	if (success)
	{
		std::cout << "process G ended successfully" << std::endl;
	}
	else
	{
		std::cout << "process G ended with code " << GetLastError() << std::endl;
	}
	return 0;
}