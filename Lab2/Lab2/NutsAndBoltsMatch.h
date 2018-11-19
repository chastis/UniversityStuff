#pragma once
#include <unordered_map>
#include <iostream>

using std::cout;
using std::endl;
using std::unordered_map;
using std::swap;

class NutsAndBoltsMatch
{
private:
	static void printArray(char array[], int n);
	static int partition(char arr[], int low, int high, char pivot);
	static void matchPairs(char nuts[], char bolts[], int low, int high);
public:
	static void HashMatch(char nuts[], char bolts[], int n);
	static void PartitionMatch(char nuts[], char bolts[], int n);
	NutsAndBoltsMatch();
	~NutsAndBoltsMatch();
};

