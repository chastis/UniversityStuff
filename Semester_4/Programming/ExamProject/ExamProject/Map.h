#ifndef CLASS_MAP_H
#define CLASS_MAP_H

#include "RB_tree.h"
template <typename Key, typename Value>
class map
{
	struct pair {
		Key _key;
		Value _data;

		bool operator<(const pair& rhs) const;
		bool operator>(const pair& rhs) const;
	};
	RB_Tree<pair> _container;
public:
	map() = default;
	~map() = default;
	Value& operator[](const Key& key);
};

#endif //!CLASS_MAP_H

template<typename Key, typename Value>
inline bool map<Key, Value>::pair::operator<(const pair & rhs) const
{
	return _key < rhs._key;
}

template<typename Key, typename Value>
inline bool map<Key, Value>::pair::operator>(const pair & rhs) const
{
	return _key > rhs._key;
}

template<typename Key, typename Value>
inline Value & map<Key, Value>::operator[](const Key& key)
{
	// TODO: insert return statement here
	auto el = _container.find(pair{ key, Value{} });
	if (el == _container.end()) {
		pair t = { key, Value{} };
		return _container.add(t)->_data;
	}
	return el->_data;
}
