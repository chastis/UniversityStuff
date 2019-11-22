#include "binary_tree.h"

#include <iostream>
#include <algorithm>

#define INF 2e9

template <typename Tkey, typename Tdata>
OptBinSearchTree<Tkey, Tdata>::OptBinSearchTree()
{
	//ctor
}

template <typename Tkey, typename Tdata>
OptBinSearchTree<Tkey, Tdata>::~OptBinSearchTree()
{
	if (root) root->~Node();
}

template <typename Tkey, typename Tdata>
void OptBinSearchTree<Tkey, Tdata>::setData(std::vector<std::pair<Tkey, Tdata*>> data) {

	sort(data.begin(), data.end());
	this->data = data;

	weights.resize(data.size());
	for (int i = 0; i < data.size(); i++)
		weights[i] = data[i].second->frequency;
}

template <typename Tkey, typename Tdata>
void OptBinSearchTree<Tkey, Tdata>::setWeights(std::vector<int> weights) {
	this->weights = weights;
}

template <typename Tkey, typename Tdata>
int OptBinSearchTree<Tkey, Tdata>::calcOptTree(int l, int r) {

	if (l >= r) return 0;
	if (dp[l][r].first != INF) return dp[l][r].first;

	for (int k = l; k <= r; k++) {
		int cost = calcOptTree(l, k - 1) + sum(l, k - 1) + calcOptTree(k + 1, r) + sum(k + 1, r);
		if (cost < dp[l][r].first) dp[l][r] = std::make_pair(cost, k);
	}
	return dp[l][r].first;
}

template <typename Tkey, typename Tdata>
int OptBinSearchTree<Tkey, Tdata>::calcOptTree() {
	return calcOptTree(0, weights.size() - 1);
}

template <typename Tkey, typename Tdata>
void OptBinSearchTree<Tkey, Tdata>::calcPartSums() {

	partSums.resize(weights.size());

	partSums[0] = weights[0];
	for (int i = 1; i < weights.size(); i++)
		partSums[i] = partSums[i - 1] + weights[i];
}

template <typename Tkey, typename Tdata>
int OptBinSearchTree<Tkey, Tdata>::sum(int l, int r) {

	if (l > r) return 0;
	return (partSums[r] - (l == 0 ? 0 : partSums[l - 1]));
}

template <typename Tkey, typename Tdata>
void OptBinSearchTree<Tkey, Tdata>::initTable() {
	int n = weights.size();

	dp.resize(n);
	for (int i = 0; i < n; i++) {

		dp[i].resize(n);
		for (int j = 0; j < n; j++)
			dp[i][j] = std::make_pair(INF, -1);

		dp[i][i] = std::make_pair(0, i);
	}
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* OptBinSearchTree<Tkey, Tdata>::buildOptTree() {

	initTable();
	calcPartSums();
	calcOptTree();

	delete root;
	root = buildOptTree(0, weights.size() - 1);

	return root;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* OptBinSearchTree<Tkey, Tdata>::buildOptTree(int l, int r) {

	if (l > r) return nullptr;
	int optRoot = dp[l][r].second;

	Node<Tkey, Tdata>* result = new Node<Tkey, Tdata>(data[optRoot].first, data[optRoot].second);

	Node<Tkey, Tdata>* leftChild = buildOptTree(l, optRoot - 1);
	if (leftChild) leftChild->parent = result;

	Node<Tkey, Tdata>* rightChild = buildOptTree(optRoot + 1, r);
	if (rightChild) rightChild->parent = result;

	result->left = leftChild;
	result->right = rightChild;

	return result;
}


template <typename Tkey, typename Tdata>
void OptBinSearchTree<Tkey, Tdata>::print(Node<Tkey, Tdata>* node, int deep) {

	if (!node) return;

	print(node->left, deep + 1);

	printTab(deep);
	std::cout << ">";
	node->data->print();

	print(node->right, deep + 1);
}

template <typename Tkey, typename Tdata>
void OptBinSearchTree<Tkey, Tdata>::print() {
	std::cout << "--------------------------------------------------------------------\n";
	print(root, 0);
	std::cout << "--------------------------------------------------------------------\n";
}

template <typename Tkey, typename Tdata>
void OptBinSearchTree<Tkey, Tdata>::printTab(int k) {
	for (int i = 0; i < k; i++)
		std::cout << "        ";
}