#ifndef DATA_H
#define DATA_H

#include "helpers.h"

class Data
{
public:
	Data(long long, long long, size_t);
	Data(const std::string &);
	Data(const std::vector<long long> &);
	~Data();
private:
	long long _min;
	long long _max;
	std::vector<long long> _data;
};

#endif // !DATA_H
