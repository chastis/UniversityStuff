#ifndef MUSIC_SHOP_H
#define MUSIC_SHOP_H
#include <string>
#include <vector>

using std::string;
using std::vector;

bool operator<(const std::string &a, const std::string &b)
{
	size_t min_len = a.size() < b.size() ? a.size() : b.size();
	for (int i = 0; i < min_len; i++)
	{
		if (a[i] < b[i]) return true;
		else if (a[i] > b[i]) return false;
	}
	if (a.size() < b.size()) return true;
	return false;
}

bool operator>(const std::string &a, const std::string &b)
{
	size_t min_len = a.size() < b.size() ? a.size() : b.size();
	for (int i = 0; i < min_len; i++)
	{
		if (a[i] > b[i]) return true;
		else if (a[i] < b[i]) return false;
	}
	if (a.size() > b.size()) return true;
	return false;
}

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