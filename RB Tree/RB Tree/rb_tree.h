#ifndef RB_TREE
#define RB_TREE

#include <string>

class RB_Tree;
class RB_Node;
struct Pair;
void create_new_node(RB_Node *, RB_Node *, const Pair &, bool, bool);

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


class RB_Node
{
public:
	friend class RB_Tree;
	friend void create_new_node(RB_Node *, RB_Node *, const Pair &, bool, bool);
	RB_Node();
private:
	Pair _data;
	RB_Node * _left;
	RB_Node * _right;
	RB_Node * _prev;
	bool _is_black;

};

class RB_Tree
{
public:
	friend void create_new_node(RB_Node *, RB_Node *, const Pair &, bool, bool);
	RB_Tree();
	void add(const Pair &data);
	std::string find(const std::string &key);
	void print();
private:
	RB_Node * _head;
	void print_rec(RB_Node *);
};
#endif // !RB_TREE
