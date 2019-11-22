#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <stack>
#include <limits>

using std::string;
using std::shared_ptr;
using std::vector;

template <class Key>
struct Node
{
	vector<Key> keys;
	vector<shared_ptr<Node>> sons;
	bool is_leaf;
	size_t size() { return keys.size(); }
	void resize(int size) { keys.resize(size); sons.resize(size + 1); }
	Node() :is_leaf(false)
	{
	}
	void reserveSize(int size) { keys.reserve(size); sons.reserve(size); }
	Node(const Key& key) :keys(1, key), is_leaf(false)
	{
	}
};

template <typename Key, typename Value>
struct LeafNode : public Node<Key>
{
	shared_ptr<LeafNode> next;
	vector<Value> values;
	void resize(int size) { Node<Key>::resize(size); values.resize(size); }
	LeafNode(const Key& key, const Value& val, LeafNode* nx = nullptr) : Node<Key>(key), values(1, val), next(nx) { Node<Key>::is_leaf = true; }
	LeafNode() { Node<Key>::is_leaf = true; }
};


template <typename Key, typename Value>
class BPlusTree
{
private:
	using Leaf = LeafNode<Key, Value>;
	using node_ptr = shared_ptr<Node<Key> >;
	using leaf_ptr = shared_ptr<Leaf>;
	node_ptr root_ = nullptr;
	int degree_;
	static bool changeOnPath(std::stack<std::pair<shared_ptr<Node<Key> >, int>> path, const Key& old_key, const Key& new_key);
	void splitNode(const node_ptr& parent, int full_son);
	void insertNonFull(const node_ptr& start_node, const Key& key, const Value& value);

public:
	BPlusTree(int deg) :degree_(deg) {}
	void insert(const Key& key, const Value& value);
	void remove(const Key& key);
	void writeToFile(const string& filename);
	const Value& find(const Key& key);
	void showLeaves();
	~BPlusTree() {}
};


template <typename Key, typename Value>
bool BPlusTree<Key, Value>::changeOnPath(std::stack<std::pair<shared_ptr<Node<Key> >, int>> path, const Key& old_key,
	const Key& new_key)
{
	std::pair<shared_ptr<Node<Key> >, int> parent_info = path.top();
	shared_ptr<Node<Key> > parent = parent_info.first;
	int son_index = parent_info.second;
	bool key_found = false;
	int i = 0;
	while (!path.empty() && !key_found)
	{
		i = 0;
		while (i < parent->keys.size() && parent->keys[i] != old_key)
			i++;
		if (i < parent->keys.size())
			key_found = true;
		else
		{
			parent = path.top().first;
			son_index = path.top().second;
			path.pop();
		}
	}
	if (key_found)
		parent->keys[i] = new_key;
	return key_found;
}

template <typename Key, typename Value>
void BPlusTree<Key, Value>::splitNode(const node_ptr& parent, int full_son_index)
{
	node_ptr son = parent->sons[full_son_index];
	node_ptr new_son;
	if (son->is_leaf)
		new_son = std::make_shared<Leaf>();
	else
		new_son = std::make_shared<Node<Key> >();
	new_son->reserveSize(degree_);
	int middle = son->keys.size() / 2;
	parent->keys.insert(parent->keys.begin() + full_son_index, son->keys[middle]);
	parent->sons.insert(parent->sons.begin() + full_son_index + 1, new_son);

	for (int i = degree_; i < son->size(); i++)
		new_son->keys.push_back(son->keys[i]);

	if (!son->is_leaf)
	{
		for (int i = degree_; i < son->sons.size(); i++)
			new_son->sons.push_back(son->sons[i]);
		son->resize(degree_ - 1);
	}
	else
	{
		leaf_ptr new_son_leaf = std::static_pointer_cast<Leaf>(new_son);
		leaf_ptr son_leaf = std::static_pointer_cast<Leaf>(son);
		for (int i = degree_; i < son_leaf->values.size(); i++)
		{
			new_son_leaf->values.push_back(son_leaf->values[i]);
		}
		new_son_leaf->next = son_leaf->next;
		son_leaf->next = new_son_leaf;
		son_leaf->resize(degree_);
	}
}

template <typename Key, typename Value>
void BPlusTree<Key, Value>::insertNonFull(const node_ptr& start_node, const Key& key, const Value& value)
{
	if (start_node->is_leaf)
	{
		leaf_ptr leaf_node = std::static_pointer_cast<Leaf>(start_node);
		int i = 0;
		while (i < leaf_node->size() && leaf_node->keys[i] < key)
			i++;
		leaf_node->keys.insert(leaf_node->keys.begin() + i, key);
		leaf_node->values.insert(leaf_node->values.begin() + i, value);
	}
	else
	{
		int i = 0;
		while (i < start_node->size() && start_node->keys[i] < key)
			i++;
		node_ptr next_node = start_node->sons[i];
		if (next_node->size() == 2 * degree_ - 1)
		{
			splitNode(start_node, i);
			if (key > start_node->keys[i])
				++i;
		}
		insertNonFull(start_node->sons[i], key, value);
	}
}



template <typename Key, typename Value>
void BPlusTree<Key, Value>::insert(const Key& key, const Value& value)
{
	if (root_ == nullptr)
	{
		root_ = std::make_shared<Leaf>(key, value);
		return;
	}

	if (root_->size() == 2 * degree_ - 1)
	{
		node_ptr new_root = std::make_shared<Node<Key> >();
		new_root->sons.push_back(root_);
		root_ = new_root;
		splitNode(root_, 0);
		insertNonFull(root_, key, value);
	}
	else
	{
		insertNonFull(root_, key, value);
	}
}

template <typename Key, typename Value>
void BPlusTree<Key, Value>::remove(const Key& key)
{
	std::stack<std::pair<shared_ptr<Node<Key> >, int>> path;
	shared_ptr<Node<Key> > iter = root_;
	std::pair<shared_ptr<Node<Key> >, int> key_node;
	while (!iter->is_leaf)
	{

		int i = 0;
		while (i < iter->keys.size() && key > iter->keys[i])
			i++;
		if (i < iter->keys.size() && key == iter->keys[i])
		{
			key_node.first = iter;
			key_node.second = i;
		}
		path.push(std::make_pair(iter, i));
		iter = iter->sons[i];
	}
	int key_index = 0;
	while (key_index < iter->keys.size() && key != iter->keys[key_index])
		key_index++;

	if (key_index >= iter->keys.size())
		return;
	leaf_ptr leaf_node = std::static_pointer_cast<Leaf>(iter);
	leaf_node->keys.erase(leaf_node->keys.begin() + key_index);
	leaf_node->values.erase(leaf_node->values.begin() + key_index);
	if (iter != root_ && leaf_node->size() < degree_ - 1)
	{
		std::pair<shared_ptr<Node<Key> >, int> parent_info = path.top();
		shared_ptr<Node<Key> > parent = parent_info.first;
		int son_index = parent_info.second;
		if (son_index > 0 && parent->sons[son_index - 1]->size() > degree_ - 1)
		{
			leaf_ptr left_sibling = std::static_pointer_cast<Leaf>(parent->sons[son_index - 1]);
			Key max_key = left_sibling->keys.back();
			Value max_value = left_sibling->values.back();
			left_sibling->keys.pop_back();
			left_sibling->values.pop_back();

			leaf_node->keys.insert(leaf_node->keys.begin(), max_key);
			leaf_node->values.insert(leaf_node->values.begin(), max_value);
			Key new_max_key = left_sibling->keys.back();
			if (key_node.first)
				key_node.first->keys[key_node.second] = leaf_node->keys.back();
			changeOnPath(path, max_key, new_max_key);
			/*while (!path.empty() && parent->keys[son_index - 1] != max_key)
			{
			parent = path.top().first;
			son_index = path.top().second;
			path.pop();
			}
			if (parent->keys[son_index - 1] == max_key)
			parent->keys[son_index - 1] = new_max_key;*/

			return;

		}
		if (son_index < parent->sons.size() - 1 && parent->sons[son_index + 1]->size() > degree_ - 1)
		{
			leaf_ptr right_sibling = std::static_pointer_cast<Leaf>(parent->sons[son_index + 1]);
			Key min_key = right_sibling->keys.front();
			Value min_value = right_sibling->values.front();
			right_sibling->keys.erase(right_sibling->keys.begin());
			right_sibling->values.erase(right_sibling->values.begin());

			leaf_node->keys.push_back(min_key);
			leaf_node->values.push_back(min_value);

			Key new_min_key = right_sibling->keys.front();
			changeOnPath(path, min_key, new_min_key);
			if (key_node.first)
				key_node.first->keys[key_node.second] = leaf_node->keys.back();
			return;
		}

		if (son_index > 0)
		{
			leaf_ptr left_sibling = std::static_pointer_cast<Leaf>(parent->sons[son_index - 1]);

			if (key_node.first)
				key_node.first->keys[key_node.second] = (leaf_node->keys.size() > 0 ? leaf_node->keys.back() : left_sibling->keys.back());

			left_sibling->keys.insert(left_sibling->keys.end(), leaf_node->keys.begin(), leaf_node->keys.end());
			left_sibling->values.insert(left_sibling->values.end(), leaf_node->values.begin(), leaf_node->values.end());
			parent->sons.erase(parent->sons.begin() + son_index);
			parent->keys.erase(parent->keys.begin() + son_index - 1);


		}
		else if (son_index < parent->sons.size())
		{
			leaf_ptr right_sibling = std::static_pointer_cast<Leaf>(parent->sons[son_index + 1]);
			leaf_node->keys.insert(leaf_node->keys.end(), right_sibling->keys.begin(), right_sibling->keys.end());
			leaf_node->values.insert(leaf_node->values.end(), right_sibling->values.begin(), right_sibling->values.end());

			parent->sons.erase(parent->sons.begin() + son_index + 1);
			parent->keys.erase(parent->keys.begin() + son_index);
		}
		else
			throw std::runtime_error("Can't find node to merge!");
		while (parent != root_ && parent->size() < degree_ - 1)
		{
			path.pop();
			parent = path.top().first;
			son_index = path.top().second;
			node_ptr cur_node = parent->sons[son_index];
			if (son_index > 0 && parent->sons[son_index - 1]->size() > degree_ - 1)
			{
				node_ptr left_sibling = parent->sons[son_index - 1];
				cur_node->keys.insert(cur_node->keys.begin(), parent->keys[son_index - 1]);
				cur_node->sons.insert(cur_node->sons.begin(), left_sibling->sons.back());
				parent->keys[son_index - 1] = left_sibling->keys.back();
				left_sibling->keys.pop_back();
				left_sibling->sons.pop_back();
				break;
			}
			if (son_index < parent->sons.size() - 1 && parent->sons[son_index + 1]->size() > degree_ - 1)
			{
				node_ptr right_sibling = parent->sons[son_index + 1];
				cur_node->keys.insert(cur_node->keys.end(), parent->keys[son_index]);
				cur_node->sons.insert(cur_node->sons.end(), right_sibling->sons.front());
				parent->keys[son_index] = right_sibling->keys.front();
				right_sibling->keys.erase(right_sibling->keys.begin());
				right_sibling->sons.erase(right_sibling->sons.begin());
				break;
			}

			if (son_index > 0)
			{
				node_ptr left_sibling = parent->sons[son_index - 1];
				left_sibling->sons.insert(left_sibling->sons.end(), leaf_node->sons.begin(), leaf_node->sons.end());
				left_sibling->keys.push_back(parent->keys[son_index - 1]);
				left_sibling->keys.insert(left_sibling->keys.end(), leaf_node->keys.begin(), leaf_node->keys.end());
				parent->sons.erase(parent->sons.begin() + son_index);
				parent->keys.erase(parent->keys.begin() + son_index - 1);

			}
			else if (son_index < parent->sons.size())
			{
				node_ptr right_sibling = parent->sons[son_index + 1];
				cur_node->sons.insert(cur_node->sons.end(), right_sibling->sons.begin(), right_sibling->sons.end());
				cur_node->keys.push_back(parent->keys[son_index]);
				cur_node->keys.insert(cur_node->keys.end(), right_sibling->keys.begin(), right_sibling->keys.end());

				parent->keys.erase(parent->keys.begin() + son_index);
				parent->sons.erase(parent->sons.begin() + son_index + 1);
			}
			else
				throw std::runtime_error("Can't find node to merge!");
		}
		if (root_->size() == 0)
			root_ = root_->sons.front();
	}
	else
	{
		if (key_node.first)
			key_node.first->keys[key_node.second] = leaf_node->keys.back();
		//changeOnPath(path, key, leaf_node->keys.back());
	}
}

template <typename Key, typename Value>
void BPlusTree<Key, Value>::writeToFile(const string& filename)
{
	std::ofstream file(filename);
	if (!file.is_open())
	{
		std::cout << "Cant open a file!\n";
		return;
	}
	file << "digraph g {\n\tsplines=false;\n";
	file << "\tnode [shape=record]\n";
	//int node_index = 0;
	std::queue< std::pair< node_ptr, int > > nodes;
	nodes.push(std::make_pair(root_, 0));
	while (!nodes.empty())
	{
		std::pair<node_ptr, int> front = nodes.front();
		node_ptr top = front.first;
		int node_index = front.second;
		nodes.pop();
		if (!top->is_leaf)
		{
			file << "\tnode" << node_index << " [label = \"{{";
			for (int i = 0; i < top->keys.size(); i++)
			{
				file << "<k" << i << "> " << top->keys[i];
				if (i != top->keys.size() - 1)
					file << " | ";
			}
			file << "} | {";
			{
				for (int i = 0; i < top->sons.size(); i++)
				{
					file << "<l" << i << "> *";
					if (i != top->sons.size() - 1)
						file << " | ";
					nodes.push(std::make_pair(top->sons[i], 2 * degree_ * node_index + i + 1));
				}
				file << "}}\"]\n";
				for (int i = 0; i < top->sons.size(); i++)
				{
					file << "\tnode" << node_index << ":<l" << i << "> -> " << "node" << 2 * degree_ * node_index + i + 1 << "\n";
				}

			}
		}
		else
		{
			file << "\tnode" << node_index << " [label = \"";
			leaf_ptr leaf = std::static_pointer_cast<Leaf>(top);
			for (int i = 0; i < leaf->values.size(); i++)
			{
				file << "{<k" << i << "> " << leaf->keys[i] << " | <v" << i << "> " << leaf->values[i] << "}";
				if (i != leaf->values.size() - 1)
					file << " | ";
			}
			file << "\"]\n";
		}

	}

	file << "}\n";
	file.close();
}

template <typename Key, typename Value>
const Value& BPlusTree<Key, Value>::find(const Key& key)
{
	node_ptr iter = root_;
	while (!iter->is_leaf)
	{
		int i = 0;
		while (i < iter->keys.size() && key > iter->keys[i])
			i++;
		iter = iter->sons[i];
	}
	int i = 0;
	while (i < iter->keys.size() && key != iter->keys[i])
		i++;
	if (i >= iter->keys.size())
		return Value();
	else
	{
		leaf_ptr node = std::static_pointer_cast<Leaf>(iter);
		return node->values[i];
	}
}

template <typename Key, typename Value>
void BPlusTree<Key, Value>::showLeaves()
{
	using std::cout;
	using std::endl;
	auto iter = root_;
	while (!iter->is_leaf)
	{
		iter = iter->sons[0];
	}
	auto leaf_iter = std::static_pointer_cast<Leaf>(iter);
	while (leaf_iter)
	{
		cout << "---------\n";
		for (int i = 0; i < leaf_iter->size(); i++)
		{
			cout << leaf_iter->keys[i] << " - " << leaf_iter->values[i] << endl;;
		}
		leaf_iter = leaf_iter->next;
	}
}

