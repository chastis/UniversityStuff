#ifndef MUSIC_SHOP_H
#define MUSIC_SHOP_H
#include <string>
#include <vector>

using std::string;
using std::vector;

struct Album
{
	Album()
	{
		name = "";
		year = 0;
		amout_of_songs = 0;
	}
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

bool operator<(const Album &a, const Album &b)
{
	if (a.amout_of_songs < b.amout_of_songs) return true;
	return false;
}

bool operator>(const Album &a, const Album &b)
{
	if (a.amout_of_songs > b.amout_of_songs) return true;
	return false;
}

bool operator<=(const Album &a, const Album &b)
{
	if (a.amout_of_songs <= b.amout_of_songs) return true;
	return false;
}

bool operator>=(const Album &a, const Album &b)
{
	if (a.amout_of_songs >= b.amout_of_songs) return true;
	return false;
}

#endif