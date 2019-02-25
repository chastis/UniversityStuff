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
	_rate = 0;
	_number = 1;
}

RB_Tree::RB_Tree()
{
	_head = 0;
}

void update(RB_Node * temp)
{
	//https://ru.wikipedia.org/wiki/%D0%9A%D1%80%D0%B0%D1%81%D0%BD%D0%BE-%D1%87%D1%91%D1%80%D0%BD%D0%BE%D0%B5_%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE

	auto grandparent = [](RB_Node * node) -> RB_Node *
	{
		if (node != 0 && node->_prev != 0)
			return node->_prev->_prev;
		else return NULL;
	};
	auto uncle = [grandparent](RB_Node * node) -> RB_Node *
	{
		RB_Node * grand = grandparent(node);
		//no grandparent means no uncle!
		if (grand == 0) return 0;
		if (node->_prev == grand->_left)
			return grand->_right;
		else return grand->_right;

	};
	auto rotate_left = [](RB_Node * node)
	{
		RB_Node * pivot = node->_right;

		pivot->_prev = node->_prev; /* при этом, возможно, pivot становится корнем дерева */
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
	auto rotate_right = [](RB_Node * node)
	{
		RB_Node * pivot = node->_left;

		pivot->_prev = node->_prev; /* при этом, возможно, pivot становится корнем дерева */
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
	RB_Node * u = uncle(temp), *g = grandparent(temp);
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

void RB_Tree::add(const Performer &data)
{
	_size++;
	if (_head == 0)
	{
		RB_Node* temp = new RB_Node;
		temp->_data = data;
		_head = temp;
		_head->_is_black = true;
	}
	else {
		RB_Node * temp = _head;
		while (true)
		{
			temp->_number++;
			if (data.name < temp->_data.name)
				if (temp->_left)
				{
					temp = temp->_left;
					continue;
				}
				else
				{
					RB_Node * new_node = new RB_Node;
					new_node->_data = data;
					new_node->_prev = temp;
					temp->_left = new_node;

					update(new_node);
					return;
				}
			else if (data.name > temp->_data.name)
				if (temp->_right)
				{
					temp = temp->_right;
					continue;
				}
				else
				{
					RB_Node * new_node = new RB_Node;
					new_node->_data = data;
					new_node->_prev = temp;
					temp->_right = new_node;

					update(new_node);
					return;
				}
			else {
				//data already exist;
				//do nothing?
				temp->_number--;
				_size--;
				return;
			}
		}
	}
}

Performer RB_Tree::find(const std::string &key)
{
	Performer empty;
	if (_head == 0)
	{
		//this word does not exist
		
		return empty;
	}
	else
	{
		RB_Node * temp = _head;
		while (true)
		{
			if (temp->_data.name > key)
			{
				if (temp->_left)
				{
					temp = temp->_left;
					continue;
				}
				//this word does not exist
				else return empty;
			}
			else if (temp->_data.name < key)
			{
				if (temp->_right)
				{
					temp = temp->_right;
					continue;
				}
				//this word does not exist
				else return empty;
			}
			//we find IT!!!
			else
			{
				temp->_rate++;
				//if we don't have parent
				if (temp->_prev == 0) return temp->_data;
				//if we have parent and we MORE rate then he
				if (temp->_rate > temp->_prev->_rate)
				{
					//don't have grandparent
					if (temp->_prev->_prev == 0)
					{
						_head = temp;
						if (temp = temp->_prev->_right)
						{
							temp->_prev->_right = temp->_left;
							temp->_left = temp->_prev;
							temp->_prev = 0;
							temp->_left->_prev = temp;
							//temp->_left->_right = 0;
							update(temp->_left);
						}
						else
						{
							temp->_prev->_left = temp->_right;
							temp->_right = temp->_prev;
							temp->_prev = 0;
							temp->_right->_prev = temp;
							//temp->_right->_left = 0;
							update(temp->_right);
						}
					}
					//have grandparent;
					else
					{

						RB_Node * gran = temp->_prev->_prev;
						if (gran->_right == temp->_prev)
						{
							gran->_right = temp;
						}
						else
						{
							gran->_left = temp;
						}
						if (temp = temp->_prev->_right)
						{
							temp->_prev->_right = temp->_left;
							temp->_left = temp->_prev;
							temp->_prev = gran;
							temp->_left->_prev = temp;
							//temp->_left->_right = 0;
							update(temp->_left);
						}
						else
						{
							temp->_prev->_left = temp->_right;
							temp->_right = temp->_prev;
							temp->_prev = gran;
							temp->_right->_prev = temp;
							//temp->_right->_left = 0;
							update(temp->_right);
						}
					}
				}

				//done
				return temp->_data;
			}
		}
	}
}

void RB_Tree::print_rec(RB_Node * temp)
{
	if (temp->_left) print_rec(temp->_left);
	std::cout << temp->_data.name << std::endl;
	if (temp->_right) print_rec(temp->_right);
}

void RB_Tree::print()
{
	print_rec(_head);
}

Performer RB_Tree::find_i(const size_t &i)
{
	size_t j = i;
	if (j > _size)
	{
		//error
		Performer empty;
		return empty;
	}
	RB_Node * temp = _head;
	while (true)
	{
		size_t size_left = temp->_left ? temp->_left->_number : 0;
		if (temp->_number == 1 || size_left+1 == j) return temp->_data;
		if (size_left >= j)
		{
			temp = temp->_left;
		}
		else
		{
			j -= (size_left + 1);
			temp = temp->_right;
		}
	}
}