#include "rb_tree.h"
#include <iostream>

bool operator<(const std::string &a, const std::string &b)
{
	size_t min_len = a.size() < b.size() ? a.size() : b.size();
	for (int i = 0; i < min_len; i++)
	{
		if (a[i] < b[i]) return true;
		else if (a[i] > b[i]) return false;
	}
	if (a.size() < b.size()) return true;
	return false;
}

bool operator>(const std::string &a, const std::string &b)
{
	size_t min_len = a.size() < b.size() ? a.size() : b.size();
	for (int i = 0; i < min_len; i++)
	{
		if (a[i] > b[i]) return true;
		else if (a[i] < b[i]) return false;
	}
	if (a.size() > b.size()) return true;
	return false;
}

RB_Node::RB_Node()
{
	_is_black = false;
	_left = 0;
	_right = 0;
	_prev = 0;
}

RB_Tree::RB_Tree()
{
	_head = 0;
}

void create_new_node(RB_Node * grand, RB_Node * parent, const Pair &data, bool first, bool second)
{
	//https://ru.wikipedia.org/wiki/%D0%9A%D1%80%D0%B0%D1%81%D0%BD%D0%BE-%D1%87%D1%91%D1%80%D0%BD%D0%BE%D0%B5_%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE
	auto additional = [&](RB_Node * new_node)
	{
		new_node->_prev = parent;
		if (second) parent->_right = new_node;
		else parent->_left = new_node;
	};
	RB_Node * new_node = new RB_Node;
	new_node->_data = data;
	//случай 2
	//если родитель черный спокойно добавляем красный узел
	if (parent->_is_black)
		additional(new_node);
	//случай 3
	//случай 4

}

void RB_Tree::add(const Pair &data)
{
	if (_head == 0)
	{
		RB_Node* temp = new RB_Node;
		temp->_data = data;
		_head = temp;
		_head->_is_black = true;
	}
	else {
		RB_Node * temp = _head;
		RB_Node * grand = 0;
		bool first_rotate = 0, second_rotate = 0; // 0 == rotatle to left, 1 == rotate to right
		while (true)
		{
			if (data.key < temp->_data.key)
				if (temp->_left)
				{
					grand = temp;
					first_rotate = 0;
					temp = temp->_left;
					continue;
				}
				else
				{
					second_rotate = 0;
					create_new_node(grand, temp, data, first_rotate, second_rotate);
					return;
				}
			else if (data.key > temp->_data.key)
				if (temp->_right)
				{
					grand = temp;
					first_rotate = 1;
					temp = temp->_right;
					continue;
				}
				else
				{
					second_rotate = 1;
					create_new_node(grand, temp, data, first_rotate, second_rotate);
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

std::string RB_Tree::find(const std::string &key)
{
	if (_head == 0)
	{
		//this word does not exist
		return "";
	}
	else
	{
		RB_Node * temp = _head;
		while (true)
		{
			if (_head->_data.key < key)
			{
				if (temp->_left)
				{
					temp = temp->_left;
					continue;
				}
				//this word does not exist
				else return "";
			}
			else if (_head->_data.key > key)
			{
				if (temp->_right)
				{
					temp = temp->_right;
					continue;
				}
				//this word does not exist
				else return "";
			}
			//we find IT!!!
			else return temp->_data.value;
		}
	}
}

void RB_Tree::print_rec(RB_Node * temp)
{
	if (temp->_left) print_rec(temp->_left);
	std::cout << temp->_data.key << " " << temp->_data.value << std::endl;
	if (temp->_right) print_rec(temp->_right);
}

void RB_Tree::print()
{
	print_rec(_head);
}