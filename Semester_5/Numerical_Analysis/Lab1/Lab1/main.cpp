#include <iostream>

#define OUT  

namespace Math
{
	// Tolerance
	float eps = 0.0001;
	// Max iterations count
	int maxIterationsCount = 10000000;
	// Stationary Point for Newton's Method
	float stationaryPoint = 5.f;
	// Lambda for method of simple Iterations
	float Lambda = 0.1f;
}

float function(float x)
{
	return (x * x * x - 2 * x * x + 3);
}

float df(float x)
{
	return (3 * x * x - 4 * x);
}

// return true if answer by bisection was fond
bool bisection(float leftValue, float rightValue, float& OUT answer)
{
	if (function(leftValue)*function(rightValue)>=0.f)
	{
		std::cout << "Error : Function in Left and Right values have same sign";
		return false;
	}
	int i = 0;
	while (i++ < Math::maxIterationsCount && rightValue - leftValue >= Math::eps)
	{
		const float middleValue = (leftValue + rightValue) / 2.f;
		if (function(middleValue)==0.f)
		{
			answer = middleValue;
			return true;
		}
		else if (function(leftValue)*function(middleValue) < 0.f)
		{
			rightValue = middleValue;
		}
		else
		{
			leftValue = middleValue;
		}
		std::cout << "mv = " << middleValue << std::endl;
	}
	return false;
}

// return true if answer by bisection was fond
bool newtonMethod(float& OUT answer)
{
	float x = Math::stationaryPoint;
	int i = 0;
	float prevX = x+1;
	while (i++ < Math::maxIterationsCount && abs(prevX - x) >= Math::eps)
	{
		prevX = x;
		x = x - function(x) / df(x);
		std::cout << "x = " << x << std::endl;
	}
	answer = x;
	return true;
}

// return true if answer by bisection was fond
bool simpleIteration(float& OUT answer)
{
	float x = Math::stationaryPoint;
	int i = 0;
	float prevX = x + 1;
	while (i++ < Math::maxIterationsCount && abs(prevX - x) >= Math::eps)
	{
		prevX = x;
		x = x - function(x) * Math::Lambda;
		std::cout << "x = " << x << std::endl;
	}
	answer = x;
	return true;
}

int main()
{
	const float left = -10.f, right = 20.f;
	float answer = 0.f;
	if (simpleIteration(answer))
	{
		std::cout << "y = 0 in x = " << answer << std::endl;
	}
	else
	{
		std::cout << "Can't find point where y = 0" << std::endl;
	}
	return 0;
}