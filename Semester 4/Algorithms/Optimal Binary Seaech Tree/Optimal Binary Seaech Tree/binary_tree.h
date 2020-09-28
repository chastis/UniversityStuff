#ifndef OPTBINSEARCHTREE_H
#define OPTBINSEARCHTREE_H

#include "Node.h"
#include <vector>

template <typename Tkey, typename Tdata>
class OptBinSearchTree
{
public:
	OptBinSearchTree();
	virtual ~OptBinSearchTree();

	int calcOptTree();
	int calcOptTree(int l, int r);
	Node<Tkey, Tdata>* buildOptTree();
	void setData(std::vector<std::pair<Tkey, Tdata*>> data);
	void setWeights(std::vector<int> weights);
	void print();

private:
	Node<Tkey, Tdata>* root = nullptr;

	std::vector<std::pair<Tkey, Tdata*>> data;
	std::vector<int> weights;
	std::vector<int> partSums;
	std::vector<std::vector<std::pair<long long, int>>> dp;


	void calcPartSums();
	int sum(int l, int r);
	void initTable();
	Node<Tkey, Tdata>* buildOptTree(int l, int r);
	void print(Node<Tkey, Tdata>* node, int deep);
	void printTab(int k);
};

#endif // OPTBINSEARCHTREE_H
