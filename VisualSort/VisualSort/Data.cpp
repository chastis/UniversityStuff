#include "Data.h"


Data::Data(long long min, long long max, size_t size) : _min(min), _max(max), _data(size)
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<long long> uid(min, max);
	std::generate_n(_data.begin(), size, [&]() {return uid(dre); });
}
Data::Data(const std::string & file)
{
	std::ifstream fin(file);
	long long temp;
	while (fin >> temp)
		_data.push_back(temp);
	fin.close();
}
Data::Data(const std::vector<long long> & data) : _data(data)
{

}

Data::~Data()
{
}
