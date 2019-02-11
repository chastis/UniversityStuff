#ifndef MUSIC_SHOP_H
#define MUSIC_SHOP_H
#include <string>
#include <vector>

struct Album
{

	std::string name;
	size_t year;
	size_t amout_of_songs;
};

struct Performer
{
	std::string name;
	std::vector<Album> albums;
};


#endif