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
	RB_Node * _parent;
	RB_Node * _prev;
	RB_Node * _next;
	bool _is_black;

};

template <class T>
class RB_Tree
{
public:
	template <class T> friend void update(RB_Node<T> * temp);
	RB_Tree();

	class iterator {
	private:
		RB_Node<T>* curr;
	public:
		iterator();
		iterator(RB_Node<T>* node);

		iterator& operator++(); //++it
		iterator operator++(int); //it++

		bool operator==(const iterator& rhs) const;
		bool operator!=(const iterator& rhs) const;

		T& operator*();
		T* operator->();
	};

	iterator add(const T &data);
	iterator find(const T &key);
	void print();



	iterator begin();
	iterator end();


private:
	RB_Node<T> * _head;
	void print_rec(RB_Node<T> *);
};

template <class T>
RB_Node<T>::RB_Node()
{
	_is_black = false;
	_left = nullptr;
	_right = nullptr;
	_parent = nullptr;
	_prev = nullptr;
	_next = nullptr;
}

template <class T>
RB_Tree<T>::RB_Tree()
{
	_head = nullptr;
}

template <class T>
void update(RB_Node<T> * temp)
{
	//https://ru.wikipedia.org/wiki/%D0%9A%D1%80%D0%B0%D1%81%D0%BD%D0%BE-%D1%87%D1%91%D1%80%D0%BD%D0%BE%D0%B5_%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE

	auto grandparent = [](RB_Node<T> * node) -> RB_Node<T> *
	{
		if (node != 0 && node->_parent != 0)
			return node->_parent->_parent;
		else return nullptr;
	};
	auto uncle = [grandparent](RB_Node<T> * node) -> RB_Node<T> *
	{
		RB_Node<T> * grand = grandparent(node);
		//no grandparent means no uncle!
		if (grand == 0) return 0;
		if (node->_parent == grand->_left)
			return grand->_right;
		else return grand->_right;

	};
	auto rotate_left = [](RB_Node<T> * node)
	{
		RB_Node<T> * pivot = node->_right;

		pivot->_parent = node->_parent; // при этом, возможно, pivot становится корнем дерева
		if (node->_parent != 0) {
			if (node->_parent->_left == node)
				node->_parent->_left = pivot;
			else
				node->_parent->_right = pivot;
		}

		node->_right = pivot->_left;
		if (pivot->_left != 0)
			pivot->_left->_parent = node;

		node->_parent = pivot;
		pivot->_left = node;
	};
	auto rotate_right = [](RB_Node<T> * node)
	{
		RB_Node<T> * pivot = node->_left;

		pivot->_parent = node->_parent; // при этом, возможно, pivot становится корнем дерева
		if (node->_parent != 0) {
			if (node->_parent->_left == node)
				node->_parent->_left = pivot;
			else
				node->_parent->_right = pivot;
		}

		node->_left = pivot->_right;
		if (pivot->_right != 0)
			pivot->_right->_parent = node;

		node->_parent = pivot;
		pivot->_right = node;
	};
	//case 1
	if (temp->_parent == 0)
	{
		temp->_is_black = true;
		return;
	}
	//case 2
	//if parent is black we can do nothing
	if (temp->_parent->_is_black) return;
	//case 3
	//if parent and uncle are red then we have to repaint them to black but grandfather's color change to red
	//and unfortunately then do all this work for our grandfather
	RB_Node<T> * u = uncle(temp), *g = grandparent(temp);
	if (u != 0 && !u->_is_black)
	{
		temp->_parent->_is_black = true;
		u->_is_black = true;
		g->_is_black = false;
		update(g);
		return;
	}
	//case 4
	//if parent is red BUT uncle is black
	//and temp is right uncestor parent
	if (temp == temp->_parent->_right && temp->_parent == g->_left)
	{
		rotate_left(temp->_parent);
		temp = temp->_parent;
		return;
	}
	else if (temp == temp->_parent->_left && temp->_parent == g->_right)
	{
		rotate_right(temp->_parent);
		temp = temp->_parent;
		return;
	}
	//case 5
	//if parent is red BUT uncle is black
	//and temp is left uncestor parent
	temp->_parent->_is_black = true;
	g->_is_black = false;
	if (temp == temp->_parent->_left && temp->_parent == g->_left)
	{
		rotate_right(g);
		return;
	}
	else rotate_left(g);

}

template <class T>
typename RB_Tree<T>::iterator RB_Tree<T>::add(const T &data)
{
	if (_head == nullptr)
	{
		RB_Node<T>* temp = new RB_Node<T>;
		temp->_data = data;
		_head = temp;
		_head->_is_black = true;
		return iterator(_head);
	}
	else {
		RB_Node<T> * temp = _head;
		RB_Node<T> * next = nullptr;
		RB_Node<T> * prev = nullptr;
		while (true)
		{
			if (data < temp->_data) {
				next = temp;
				if (temp->_left)
				{
					temp = temp->_left;
					continue;
				}
				else
				{
					RB_Node<T> * new_node = new RB_Node<T>;
					new_node->_data = data;
					new_node->_parent = temp;
					new_node->_prev = prev;
					new_node->_next = next;
					if (prev != nullptr) prev->_next = new_node;
					if (next != nullptr) next->_prev = new_node;
					temp->_left = new_node;

					update(new_node);
					return iterator(new_node);
				}
			}
			else if (data > temp->_data) {
				prev = temp;
				if (temp->_right)
				{
					temp = temp->_right;
					continue;
				}
				else
				{
					RB_Node<T> * new_node = new RB_Node<T>;
					new_node->_data = data;
					new_node->_parent = temp;
					new_node->_prev = prev;
					new_node->_next = next;
					if (prev != nullptr) prev->_next = new_node;
					if (next != nullptr) next->_prev = new_node;
					temp->_right = new_node;

					update(new_node);
					return iterator(new_node);
				}
			}
			else return iterator(temp);
		}
	}
	return end();
}

template <class T>
typename RB_Tree<T>::iterator RB_Tree<T>::find(const T &key)
{
	if (_head == 0) return iterator();
	RB_Node<T> * temp = _head;
	while (true)
	{
		if (temp->_data < key)
		{
			if (temp->_left) temp = temp->_left;
			else return iterator();
		}
		else if (temp->_data > key)
		{
			if (temp->_right) temp = temp->_right;
			else return iterator();
		}
		else return iterator(temp);
	}
}

template<class T>
inline typename RB_Tree<T>::iterator RB_Tree<T>::begin()
{
	RB_Node<T> * beg = _head;
	while (beg->_prev != nullptr)
		beg = beg->_prev;
	return iterator(beg);
}

template<class T>
inline typename RB_Tree<T>::iterator RB_Tree<T>::end()
{
	return iterator();
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

#endif // !RB_TREE_H

template<class T>
inline RB_Tree<T>::iterator::iterator()
{
	curr = nullptr;
}

template<class T>
inline RB_Tree<T>::iterator::iterator(RB_Node<T>* node)
{
	curr = node;
}

template<class T>
inline typename RB_Tree<T>::iterator & RB_Tree<T>::iterator::operator++()
{
	// TODO: insert return statement here
	curr = curr->_next;
	return *this;
}

template<class T>
inline typename RB_Tree<T>::iterator RB_Tree<T>::iterator::operator++(int)
{
	iterator ret(curr);
	curr = curr->_next;
	return ret;
}

template<class T>
inline bool RB_Tree<T>::iterator::operator==(const iterator & rhs) const
{
	return curr == rhs.curr;
}

template<class T>
inline bool RB_Tree<T>::iterator::operator!=(const iterator & rhs) const
{
	return curr != rhs.curr;
}

template<class T>
inline T & RB_Tree<T>::iterator::operator*()
{
	// TODO: insert return statement here
	return curr->_data;
}

template<class T>
inline T * RB_Tree<T>::iterator::operator->()
{
	return &(curr->_data);
}
