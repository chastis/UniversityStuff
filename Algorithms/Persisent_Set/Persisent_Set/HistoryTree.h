#pragma once
#include<initializer_list>
#include<list>
#include<set>
#include<unordered_map>
#include<memory>
#include<fstream>
#include<string>
#include<iterator>
#include"Tree.h"
using std::string;
using std::ofstream;

template<class T>
class HistoryTree {
private:
	typedef typename RBTree<T>::Node NodeType;
	typedef std::shared_ptr<const NodeType> node_ptr_type;

	std::list<RBTree<T> > history_list;
	std::unordered_map<const NodeType*, int> arr;

	void bst_print_dot_null(const string& name, int nullcount, ofstream& fout) {
		fout << "    null" << nullcount << "[shape=point];\n";
		fout << "    " << name << " -> null" << nullcount << ";\n";
	}

	void bst_print_dot_aux(node_ptr_type node, ofstream& fout) {
		static int nullcount = 0;

		string parent = "node" + std::to_string(arr[node.get()]);
		fout << "    " << parent << "[fontcolor=white, label=\"{" << node->_val;
		//fout << "|links:" << node.use_count();
		fout << "}\"";
		fout << "style=filled, fillcolor=" << (node->_c ? "black" : "red") << "];\n";

		if (node->_lft != nullptr)
		{
			fout << "    " << parent << " -> " << "node" << arr[node->_lft.get()] << ";\n";
			bst_print_dot_aux(node->_lft, fout);
		}
		else {
			//bst_print_dot_null(parent, nullcount++, fout);
		}

		if (node->_rgt != nullptr)
		{
			fout << "    " << parent << " -> " << "node" << arr[node->_rgt.get()] << ";\n";
			bst_print_dot_aux(node->_rgt, fout);
		}
		else {
			//bst_print_dot_null(parent, nullcount++, fout);
		}
	}
	void PrintTree(const std::string &path)
	{
		ofstream fout(path);

		fout << "digraph BST {\n";
		fout << "    node [fontname=\"Arial\"\n    fontsize = \"16\"\n    shape = \"record\"];\n";

		for (auto it = history_list.begin(); it != history_list.end(); ++it)
		{
			node_ptr_type tree = it->_root;
			if (tree == nullptr)
				fout << "\n";
			else if (tree->_rgt == nullptr && tree->_lft == nullptr)
				fout << "    \"" << tree->_val << "\";\n";
			else
				bst_print_dot_aux(tree, fout);
		}

		fout << "}\n";
		fout.close();
	}
public:
	HistoryTree(const std::initializer_list<RBTree<T>> &init) : history_list(init) {}
	void PrintForViz(const std::string &path)
	{
		arr.clear();
		int index = 0;

		for (auto &tr : history_list)
		{
			auto items = tr.items();
			for (auto itr = items.begin(); itr != items.end(); ++itr)
			{
				typename std::unordered_map<const NodeType*, int>::iterator isPresented =
					arr.find(itr->get());
				if (isPresented == arr.end())
				{
					arr.emplace(itr->get(), index++);
				}
			}
		}
		this->PrintTree(path);
	}
};