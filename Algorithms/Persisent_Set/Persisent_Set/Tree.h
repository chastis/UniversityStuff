#pragma once
#pragma once
#include<memory>
#include<list>
#include<set>
#include<stack>
#include<cassert>

template<class T>
class HistoryTree;

template<typename T>
class RBTree {
private:
	struct Node;
	friend class HistoryTree<T>;
	typedef std::shared_ptr<const Node> node_ptr_type;
	enum Color { Red, Black };

	struct Node
	{
		friend class HistoryTree<T>;
		Node(Color c, std::shared_ptr<const Node> const & lft, T val,
			std::shared_ptr<const Node> const & rgt)
			: _c(c), _lft(lft), _val(val), _rgt(rgt)
		{}
		Color _c;
		std::shared_ptr<const Node> _lft;
		T _val;
		std::shared_ptr<const Node> _rgt;
	};

	RBTree ins(T x) const
	{
		if (isEmpty())
			return RBTree(Red, RBTree(), x, RBTree());
		T y = root();
		Color c = rootColor();
		if (x < y)
			return balance(c, left().ins(x), y, right());
		else if (y < x)
			return balance(c, left(), y, right().ins(x));
		else
			return *this; // no duplicates
	}
	RBTree del(T x) const
	{
		T y = root();
		Color c = rootColor();

	}
	static RBTree balance(Color c, RBTree const & lft, T x, RBTree const & rgt)
	{
		if (c == Black && lft.doubledLeft())
			return RBTree(Red, lft.left().paint(Black)
				, lft.root(), RBTree(Black, lft.right(), x, rgt));
		else if (c == Black && lft.doubledRight())
			return RBTree(Red
				, RBTree(Black, lft.left(), lft.root(), lft.right().left())
				, lft.right().root(), RBTree(Black, lft.right().right(), x, rgt));
		else if (c == Black && rgt.doubledLeft())
			return RBTree(Red, RBTree(Black, lft, x, rgt.left().left())
				, rgt.left().root(), RBTree(Black, rgt.left().right(), rgt.root(), rgt.right()));
		else if (c == Black && rgt.doubledRight())
			return RBTree(Red, RBTree(Black, lft, x, rgt.left())
				, rgt.root(), rgt.right().paint(Black));
		else
			return RBTree(c, lft, x, rgt);
	}
	bool doubledLeft() const {
		return !isEmpty()
			&& rootColor() == Red
			&& !left().isEmpty()
			&& left().rootColor() == Red;
	}
	bool doubledRight() const {
		return !isEmpty()
			&& rootColor() == Red
			&& !right().isEmpty()
			&& right().rootColor() == Red;
	}
	RBTree paint(Color c) const {
		assert(!isEmpty());
		return RBTree(c, left(), root(), right());
	}

	Color rootColor() const {
		assert(!isEmpty());
		return _root->_c;
	}
	bool isEmpty() const { return !_root; }
	T root() const {
		assert(!isEmpty());
		return _root->_val;
	}
	RBTree left() const {
		assert(!isEmpty());
		return RBTree(_root->_lft);
	}
	RBTree right() const {
		assert(!isEmpty());
		return RBTree(_root->_rgt);
	}

	RBTree(Color color, const RBTree const & lft, T val, const RBTree const & rgt)
		: _root(std::make_shared<const Node>(color, lft._root, val, rgt._root))
	{
		assert(lft.isEmpty() || lft.root() < val);
		assert(rgt.isEmpty() || val < rgt.root());
	}
	RBTree() {}
	explicit RBTree(std::shared_ptr<const Node> const & node)
		: _root(node) {}
public:
	RBTree(const std::initializer_list<T> &init) {
		RBTree t;
		for (const T &v : init) {
			t = t.Insert(v);
		}
		_root = t._root;
	}

	RBTree Insert(T x) const {
		RBTree t = ins(x);
		return RBTree(Black, t.left(), t.root(), t.right());
	}
	void clear() {
		_root.reset();
	}
	std::list<node_ptr_type> items() const {

		std::list<node_ptr_type> out;
		std::stack<node_ptr_type> s;
		node_ptr_type curr = _root;

		while (curr != nullptr || s.empty() == false)
		{
			while (curr != nullptr)
			{
				s.push(curr);
				curr = curr->_lft;
			}

			curr = s.top();
			s.pop();

			out.push_back(curr);

			curr = curr->_rgt;

		}
		return out;
	}
private:
	std::shared_ptr<const Node> _root;
};