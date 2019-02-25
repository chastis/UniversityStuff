#include <iostream>
#include "music_shop.h"
using std::cout;
using std::cin;
using std::endl;

int main()
{
	Performer a, b, c, d;
	a.name = "AC/DC";
	b.name = "The Shins";
	c.name = "The Doors";
	d.name = "Queen";
	Hash h;
	h.add(a);
	h.add(b);
	h.add(c);
	h.add(d);
	cout << h.get(a.name).name << endl;
	cout << h.get(b.name).name << endl;
	cout << h.get(c.name).name << endl;
	cout << h.get(d.name).name << endl;

	cout << "That's all, Folks!" << endl;
	cin.get();
	return 0;
}
