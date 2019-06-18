#ifndef NODE_H
#define NODE_H

#include "Flight.h"

template <typename Tkey, typename Tdata>
class Node
{
public:
	Node(Node* parent);
	Node(const Tkey& key, Tdata* data);
	Node();
	virtual ~Node();

	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
	Tdata* data = nullptr;
	Tkey key;
};

#endif // NODE_H
