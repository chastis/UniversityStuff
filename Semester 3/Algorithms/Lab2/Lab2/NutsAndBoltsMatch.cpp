#include "NutsAndBoltsMatch.h"

void NutsAndBoltsMatch::printArray(char array[], int n)
{
	for (size_t i = 0; i < n; i++)
		cout << array[i] << " ";
	cout << endl;
}

int NutsAndBoltsMatch::partition(char arr[], int low, int high, char pivot)
{
	int i = low;
	for (int j = low; j < high; j++)
	{
		if (arr[j] < pivot)
		{
			swap(arr[i], arr[j]);
			i++;
		}
		else if (arr[j] == pivot)
		{
			swap(arr[j], arr[high]);
			j--;
		}
	}
	swap(arr[i], arr[high]);

	// Return the partition index of an array based on the pivot  
	// element of other array. 
	return i;
}

void NutsAndBoltsMatch::matchPairs(char nuts[], char bolts[], int low, int high)
{
	if (low < high)
	{
		// Choose last character of bolts array for nuts partition. 
		int pivot = partition(nuts, low, high, bolts[high]);

		// Now using the partition of nuts choose that for bolts 
		// partition. 
		partition(bolts, low, high, nuts[pivot]);

		// Recur for [low...pivot-1] & [pivot+1...high] for nuts and 
		// bolts array. 
		matchPairs(nuts, bolts, low, pivot - 1);
		matchPairs(nuts, bolts, pivot + 1, high);
	}
}

//the elements in the unordered_map are organized into buckets depending on their hash values to allow for fast 
//access to individual elements directly by their key values (with a constant average time complexity on average).
void NutsAndBoltsMatch::HashMatch(char nuts[], char bolts[], int n)
{
	unordered_map<char, int> hash;

	for (int i = 0; i < n; i++)
		hash[nuts[i]] = i;

	for (int i = 0; i < n; i++)
		if (hash.find(bolts[i]) != hash.end())
			nuts[i] = bolts[i];

	cout << "matched nuts and bolts are-" << endl;
	for (int i = 0; i < n; i++)
		cout << nuts[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << bolts[i] << " ";
	cout << endl;
}

//This algorithm first performs a partition by picking last element of bolts array as pivot, rearrange the array of 
//nuts and returns the partition index ‘i’ such that all nuts smaller than nuts[i] are on the left side and all 
//nuts greater than nuts[i] are on the right side. Next using the nuts[i] we can partition the array of bolts. 
//Partitioning operations can easily be implemented in O(n). Now we apply this partitioning recursively on the left and right sub-array of nuts and bolts.
void NutsAndBoltsMatch::PartitionMatch(char nuts[], char bolts[], int n)
{
	matchPairs(nuts, bolts, 0, n - 1);
	cout << "Matched nuts and bolts are : \n";
	printArray(nuts, n);
	printArray(bolts, n);
}

NutsAndBoltsMatch::NutsAndBoltsMatch()
{
}

NutsAndBoltsMatch::~NutsAndBoltsMatch()
{
}
