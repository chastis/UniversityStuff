#include "vocabulary.h"
#include <iostream>

using std::cout;
using std::cin;

int main()
{
	Pair one, two, three;
	one.key = "hello";
	one.value = "privet";
	two.key = "bye";
	two.value = "poka";
	three.key = "one";
	three.value = "odin";

	Hash my_h;
	my_h.add(one);
	my_h.add(two);
	my_h.add(three);
	cout << my_h.get(one.key) << endl;
	cout << my_h.get(two.key) << endl;
	cout << my_h.get(three.key) << endl;
	cin.get();
	return 0;
}