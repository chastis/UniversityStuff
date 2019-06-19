//take from https://github.com/chastis/Algorithms_Fourth_Semester/tree/master/RB%20Tree
//added template

#ifndef RB_TREE_H
#define RB_TREE_H

#include <string>

template <class T>
class RB_Tree;
template <class T>
class RB_Node;

template <class T>
void update(RB_Node<T> * temp);

template <class T>
class RB_Node
{
public:
	friend class RB_Tree<T>;
	template <class T> friend void update(RB_Node<T> * temp);
	RB_Node();
private:
	T _data;
	RB_Node * _left;
	RB_Node * _right;
	RB_Node * _prev;
	bool _is_black;

};

template <class T>
class RB_Tree
{
public:
	template <class T> friend void update(RB_Node<T> * temp);
	RB_Tree();
	void add(const T &data);
	T find(const T &key);
	void print();
private:
	RB_Node<T> * _head;
	void print_rec(RB_Node<T> *);
};

#include "RB_Tree.cpp"

#endif // !RB_TREE_H