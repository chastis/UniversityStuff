#ifndef RB_TREE_CPP
#define RB_TREE_CPP

#include "rb_tree.h"
#include <iostream>

template <class T>
RB_Node<T>::RB_Node()
{
	_is_black = false;
	_left = 0;
	_right = 0;
	_prev = 0;
}

template <class T>
RB_Tree<T>::RB_Tree()
{
	_head = 0;
}

template <class T>
void update(RB_Node<T> * temp)
{
	//https://ru.wikipedia.org/wiki/%D0%9A%D1%80%D0%B0%D1%81%D0%BD%D0%BE-%D1%87%D1%91%D1%80%D0%BD%D0%BE%D0%B5_%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE

	auto grandparent = [](RB_Node<T> * node) -> RB_Node<T> *
	{
		if (node != 0 && node->_prev != 0)
			return node->_prev->_prev;
		else return NULL;
	};
	auto uncle = [grandparent](RB_Node<T> * node) -> RB_Node<T> *
	{
		RB_Node<T> * grand = grandparent(node);
		//no grandparent means no uncle!
		if (grand == 0) return 0;
		if (node->_prev == grand->_left)
			return grand->_right;
		else return grand->_right;

	};
	auto rotate_left = [](RB_Node<T> * node)
	{
		RB_Node<T> * pivot = node->_right;

		pivot->_prev = node->_prev; // при этом, возможно, pivot становится корнем дерева
		if (node->_prev != 0) {
			if (node->_prev->_left == node)
				node->_prev->_left = pivot;
			else
				node->_prev->_right = pivot;
		}

		node->_right = pivot->_left;
		if (pivot->_left != 0)
			pivot->_left->_prev = node;

		node->_prev = pivot;
		pivot->_left = node;
	};
	auto rotate_right = [](RB_Node<T> * node)
	{
		RB_Node<T> * pivot = node->_left;

		pivot->_prev = node->_prev; // при этом, возможно, pivot становится корнем дерева
		if (node->_prev != 0) {
			if (node->_prev->_left == node)
				node->_prev->_left = pivot;
			else
				node->_prev->_right = pivot;
		}

		node->_left = pivot->_right;
		if (pivot->_right != 0)
			pivot->_right->_prev = node;

		node->_prev = pivot;
		pivot->_right = node;
	};
	//case 1
	if (temp->_prev == 0)
	{
		temp->_is_black = true;
		return;
	}
	//case 2
	//if parent is black we can do nothing
	if (temp->_prev->_is_black) return;
	//case 3
	//if parent and uncle are red then we have to repaint them to black but grandfather's color change to red
	//and unfortunately then do all this work for our grandfather
	RB_Node<T> * u = uncle(temp), *g = grandparent(temp);
	if (u != 0 && !u->_is_black)
	{
		temp->_prev->_is_black = true;
		u->_is_black = true;
		g->_is_black = false;
		update(g);
		return;
	}
	//case 4
	//if parent is red BUT uncle is black
	//and temp is right uncestor parent
	if (temp == temp->_prev->_right && temp->_prev == g->_left)
	{
		rotate_left(temp->_prev);
		temp = temp->_prev;
		return;
	}
	else if (temp == temp->_prev->_left && temp->_prev == g->_right)
	{
		rotate_right(temp->_prev);
		temp = temp->_prev;
		return;
	}
	//case 5
	//if parent is red BUT uncle is black
	//and temp is left uncestor parent
	temp->_prev->_is_black = true;
	g->_is_black = false;
	if (temp == temp->_prev->_left && temp->_prev == g->_left)
	{
		rotate_right(g);
		return;
	}
	else rotate_left(g);

}

template <class T>
void RB_Tree<T>::add(const T &data)
{
	if (_head == 0)
	{
		RB_Node<T>* temp = new RB_Node<T>;
		temp->_data = data;
		_head = temp;
		_head->_is_black = true;
	}
	else {
		RB_Node<T> * temp = _head;
		while (true)
		{
			if (data < temp->_data)
				if (temp->_left)
				{
					temp = temp->_left;
					continue;
				}
				else
				{
					RB_Node<T> * new_node = new RB_Node<T>;
					new_node->_data = data;
					new_node->_prev = temp;
					temp->_left = new_node;

					update(new_node);
					return;
				}
			else if (data > temp->_data)
				if (temp->_right)
				{
					temp = temp->_right;
					continue;
				}
				else
				{
					RB_Node<T> * new_node = new RB_Node<T>;
					new_node->_data = data;
					new_node->_prev = temp;
					temp->_right = new_node;

					update(new_node);
					return;
				}
			else {
				//data already exist;
				//do nothing?
				return;
			}
		}
	}
}

template <class T>
T RB_Tree<T>::find(const T &key)
{
	T ZeroT(0);
	if (_head == 0)
	{
		//this word does not exist
		return ZeroT;
	}
	else
	{
		RB_Node * temp = _head;
		while (true)
		{
			if (_head->_data < key)
			{
				if (temp->_left)
				{
					temp = temp->_left;
					continue;
				}
				//this word does not exist
				else return ZeroT;
			}
			else if (_head->_data > key)
			{
				if (temp->_right)
				{
					temp = temp->_right;
					continue;
				}
				//this word does not exist
				else return ZeroT;
			}
			//we find IT!!!
			else return temp->_data;
		}
	}
}

template <class T>
void RB_Tree<T>::print_rec(RB_Node<T> * temp)
{
	if (temp->_left) print_rec(temp->_left);
	std::cout << temp->_data << std::endl;
	if (temp->_right) print_rec(temp->_right);
}

template <class T>
void RB_Tree<T>::print()
{
	print_rec(_head);
}

#endif //!RB_TREE_CPP