#ifndef MUSIC_SHOP_H
#define MUSIC_SHOP_H
#include <string>
#include <vector>


using std::string;
using std::vector;

int p = 53;
int temp_size = -1;

struct Params
{
	int a;
	int b;
	int m;
};

struct Album
{

	string name;
	size_t year;
	size_t amout_of_songs;
};

struct Performer
{
	string name;
	vector<Album> albums;
};

int hash_0(const string &a)
{
	long long hash = 0;
	long long p_pow = 1;
	for (int i = 0; i < a.size(); i++)
	{
		hash += (a[i] - 'a' + 1) * p_pow;
		p_pow *= p;
	}
	return hash % temp_size;
}

void perfect_hash(std::pair<vector<vector<Performer> * >,Params> &out,const vector<Performer> &in)
{
	if (temp_size == -1) temp_size = in.size() / 2;
	out.first.clear();
	out.first.resize(temp_size);
	for (auto &now : in)
	{

	}
}

#endif