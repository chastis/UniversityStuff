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

	double answerInDouble = spos::lab1::demo::g_func<spos::lab1::demo::DOUBLE>(x);
	std::cout << "calc = " << answerInDouble << std::endl;
	UINT answer = 0;
	uint32_t wParam = 0;
	while (answerInDouble!=static_cast<int>(answerInDouble) || wParam != 32)
	{
		answerInDouble *= 10.0;
		wParam++;
	}
	answer += WM_USER + 1;
	const BOOL success = PostThreadMessageW(processID, answer, wParam, 1);
	if (success)
	{
		std::cout << "process G ended successfully with " << answerInDouble << std::endl;
	}
	else
	{
		std::cout << "process G ended with code " << GetLastError() << std::endl;
	}
	return 0;
}