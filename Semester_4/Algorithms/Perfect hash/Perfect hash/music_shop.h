#ifndef MUSIC_SHOP_H
#define MUSIC_SHOP_H
#include <string>
#include <vector>
#include <list>

using std::string;
using std::vector;

namespace gl
{
	//простое число для h0
	int p = 53;
	//количество элементов изначально
	int temp_size = 16;
	//простые числа в диапазоне (1;200)
	int prime[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199 };
}


struct Params
{
	//простое число для конкертного h
	int p;
	//количество элементов данном массиве
	int size;
};

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

class Hash
{
public:
	Hash()
	{
		data.resize(gl::temp_size);
		int i = 0;
		for (auto &now : data)
		{
			std::pair<std::vector<Performer> *, Params> temp;
			temp.second.p = gl::prime[i++];
			temp.second.size = gl::temp_size;
			temp.first = new std::vector<Performer>;
			temp.first->resize(gl::temp_size);
			now = temp;
		}
	}
	void add(const Performer &in)
	{
		int h0 = func_h0(in.name);
		int h = func_h(in.name, data[h0].second);
		if (data[h0].first->size() < h)
		{
			data[h0].first->resize(h+1);
			(*data[h0].first)[h] = in;
		}
		else
		{
			
			if (in.name != (*data[h0].first)[h].name)
			{
				//new element
				if ((*data[h0].first)[h].name == "")
				{
					(*data[h0].first)[h] = in;
				}
				//another element already exist
				else
				{
					//все погано
					//объективно
					//надо запускать все заново
					//типа коллизия произошла
					reload();
				}

			}
			//else /*elemets are equal*/ do nothing
		}
	}

	Performer get(const std::string &in)
	{
		int h0 = func_h0(in);
		int h = func_h(in, data[h0].second);
		if ((*data[h0].first)[h].name == in)
		{
			return (*data[h0].first)[h];
		}
		Performer temp;
		return temp;
	}
private:
	//массив который хранит указатель на другой массив с исполнителями и параметры для второй хэш-функции
	std::vector<std::pair<std::vector<Performer> * ,Params>> data;
	int func_h0(const std::string &in)
	{
		long long hash = 0;
		long long p_pow = 1;
		for (int i = 0; i < in.size(); i++)
		{
			hash += (in[i] - 'a' + 1) * p_pow;
			p_pow *= gl::p;
		}
		return abs(hash) % gl::temp_size;
	}
	int func_h(const std::string &in, const Params &p)
	{
		long long hash = 0;
		long long p_pow = 1;
		for (int i = 0; i < in.size(); i++)
		{
			hash += (in[i] - 'a' + 1) * p_pow;
			p_pow *= p.p;
		}
		return abs(hash) % p.size;
	}
	void reload()
	{
		gl::temp_size++;
		Hash new_hash;
		for (int i = 0; i < gl::temp_size - 1; i++)
		{
			for (int j = 0; j < gl::temp_size - 1; j++)
			{
				if ((*data[i].first)[j].name != "")
					new_hash.add((*data[i].first)[j]);
			}
			delete data[i].first;
		}
		data.resize(gl::temp_size);
		for (int i = 0; i < gl::temp_size; i++)
		{
			(*data[i].first).resize(gl::temp_size);
			for (int j = 0; j < gl::temp_size; j++)
			{
				(*data[i].first)[j] = new_hash.get((*data[i].first)[j].name);
			}
		}
	}
};

#endif