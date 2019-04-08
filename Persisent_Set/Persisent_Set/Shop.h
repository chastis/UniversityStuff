#ifndef MUSIC_SHOP_H
#define MUSIC_SHOP_H
#include <string>
#include <vector>

using std::string;
using std::vector;

struct Album
{

	string name;
	size_t year;
	size_t amout_of_songs;
};

struct Performer
{
	Performer()
	{
		name = "";
		albums.resize(0);
	}
	string name;
	vector<Album> albums;
};
#endif