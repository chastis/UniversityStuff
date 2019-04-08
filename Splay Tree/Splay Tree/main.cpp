#include <iostream>
#include "splay_tree.h"
#include "music_shop.h"

using namespace std;

int main()
{
	SplayTree<Album> tree;
	Album a;
	a.amout_of_songs = 2;
	tree.Insert(a);
	a.amout_of_songs = 10;
	tree.Insert(a);
	a.amout_of_songs = 12;
	tree.Insert(a);
	a.amout_of_songs = 5;
	tree.Insert(a);
	a.amout_of_songs = 42;
	tree.Insert(a);
	a.amout_of_songs = 1;
	tree.Insert(a);
	a.amout_of_songs = 37;
	tree.Insert(a);
	return 0;
}