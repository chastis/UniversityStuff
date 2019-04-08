#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <utility>
#include <vector>
#include <algorithm>

enum class sides
{
	left, right
};

template <class T>
bool compare(const std::pair<T, double> &a, const std::pair<T, double> &b)
{
	//if a <= b sort will be in great order
	return a.first <= b.first;
}

template <class T>
struct Node
{
	Node * left;
	Node * right;
	T data;
};

template <class T>
class Binary_Tree
{
public:
	Binary_Tree()
	{
		_root = 0;
	}
	~Binary_Tree()
	{

	}
	void create(std::vector<std::pair<T, double>> &data)
	{
		auto min_weight = [&](int start, int end, int height) -> double
		{
			//exit conditions
			if (start > end) return 0;
			if (start == end) return height * data[start].second;
			//end

			double min_w = -1;
			int min_i = -1;
			for (int i = start; i <= end; i++)
			{
				double weight = min_weight(start, i - 1, height + 1) + min_weight(i + 1, end, height + 1) + data[i].second * height;
				if (min_w == -1 || min_w > weight)
				{
					min_w = weight;
					min_i = i;
				}
			}
			return min_w;
		};
		auto min_weight = [&](int start, int end, int height, Node<T> * node) -> double
		{
			//exit conditions
			if (start > end)
			{
				node = 0;
				return 0;
			}
			if (start == end) {
				Node<T> * new_node = new Node<T>;
				new_node->data = data[start].first;
				node = new_node;
				return height * data[start].second;
			}
			//end

			double min_w = -1;
			int min_i = -1;
			for (int i = start; i <= end; i++)
			{
				double weight = min_weight(start, i - 1, height + 1) + min_weight(i + 1, end, height + 1) + data[i].second * height;
				if (min_w == -1 || min_w > weight)
				{
					min_w = weight;
					min_i = i;
				}
			}
			Node<T> * new_node = new Node<T>;
			new_node->data = data[min_i].first;
			node = new_node;
			min_weight(start, min_i - 1, height + 1, node->left) + min_weight(min_i + 1, end, height + 1, node->right) + data[i].second * height;
			return min_w;
		};
		std::sort(data.begin(), data.end(), compare);
		min_weight(0, data.size() - 1, 0, _root);

	}
private:
	Node<T> * _root;
};

#endif // !BINARY_TREE