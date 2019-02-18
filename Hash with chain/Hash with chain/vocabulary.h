#ifndef VOCABULARY_H
#define VOCABULARY_H

#define TEMP_SIZE 16
#define P 31

#include "my_list\List.h"
#include <string>
#include <vector>


struct Pair;

struct Pair
{
	Pair()
	{
		key = "";
		value = "";
	}
	std::string key;
	std::string value;
};

class Hash
{
	public:
		Hash()
		{
			data.resize(TEMP_SIZE);
			for (auto &now : data)
			{
				now = new List<Pair>;
			}
		}
		void add(const Pair &in)
		{
			int h = h0(in.key);
			data[h]->push_back(in);
		}
		std::string get(const std::string &in)
		{
			int h = h0(in);

			for (int i = 0; i < data[h]->length(); i++)
			{
				if (data[h]->get(i).key == in)
				{
					return data[h]->get(i).value;
				}
			}
			return "";
		}
	private:
		std::vector<List<Pair> * > data;
		int h0(const std::string &in)
		{
			long long hash = 0;
			long long p_pow = 1;
			for (int i = 0; i < in.size(); i++)
			{
				hash += (in[i] - 'a' + 1) * p_pow;
				p_pow *= P;
			}
			return hash % TEMP_SIZE;
		}
};

#endif
