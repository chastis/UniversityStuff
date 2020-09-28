#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <string>


using namespace std;

struct category;

struct product {
	string name;
	double price;
	category * type;
};
struct category {
	string name;
	vector<product*> products;
	category(string name) :name(name) {}
	category() {}
};


void read_from_file(string name, vector<category> & categories) {
	ifstream fin(name);

	int cnt_categories;
	fin >> cnt_categories;

	categories.resize(cnt_categories);//вектр в котором хранятся категории
	for (int i = 0; i<cnt_categories; i++) {
		int n; // n - numer of products in current category
		fin >> categories[i].name >> n;//считываем название категорие и количество элементов в ней

		categories[i].products.resize(n);
		for (int j = 0; j<n; j++) {

			categories[i].products[j] = new product;
			getline(fin, categories[i].products[j]->name);
			categories[i].products[j]->type = &categories[i];
			categories[i].products[j]->price = (int)(rand() % 1000 + 1) / 100.;//price

		}
	}

	fin.close();

}

template<class T, class Other>
struct node {
	node * parent;
	node * left;
	node * right;
	node * child;
	int degree;
	T data;
	Other other;
	bool mark;
	node(T data, Other other, node * child = nullptr) : data(data), other(other), degree(0), mark(false),
		parent(nullptr), left(nullptr), right(nullptr),
		child(child) {}
};

template<class T, class Other>
class fib_heap {
public:
	int size;
	node<T, Other> * min;
	void consolidate();
	void union_lists(node<T, Other> *& first, node<T, Other> *& second);
	void union_leafs(node<T, Other> *& first, node<T, Other> *& second);
	fib_heap() : size(0), min(nullptr) {}
	void insert(T data, Other other);
	void insert(node<T, Other> * new_node);
	pair<T, Other> get_min();
	void delete_min();
	void merge(fib_heap second);
};

template<class T, class Other>
void fib_heap<T, Other>::insert(T data, Other other) {
	auto new_node = new node<T, Other>(data, other);
	if (!size) {
		min = new_node;
		min->left = min;
		min->right = min;
	}
	else {
		auto prev_right = min->right;
		min->right = new_node;
		new_node->left = min;
		new_node->right = prev_right;
		prev_right->left = new_node;
		if (new_node->data < min->data) {
			min = new_node;
		}
	}
	size++;
}



template<class T, class Other>
void fib_heap<T, Other>::insert(node<T, Other> * new_node) {
	if (!min) {
		min = new_node;
		min->left = min;
		min->right = min;
	}
	else {
		auto prev_right = min->right;
		min->right = new_node;
		new_node->left = min;
		new_node->right = prev_right;
		prev_right->left = new_node;
		if (new_node->data < min->data) {
			min = new_node;
		}
	}

}

template <class T, class Other>
pair<T, Other> fib_heap<T, Other>::get_min() {
	return { min->data, min->other };
}

template <class T, class Other>
void fib_heap<T, Other>::union_lists(node<T, Other> *& first, node<T, Other> *& second) {

	if (!first) {
		first = second;
		return;
	}
	if (!second) return;


	auto L = first->left;
	auto R = second->right;

	second->right = first;
	first->left = second;
	L->right = R;
	R->left = L;

}

template <class T, class Other>
void fib_heap<T, Other>::union_leafs(node<T, Other> *& first, node<T, Other> *& second) {

	if (!first) {
		first = second;
		first->left = first;
		first->right = second;
		return;
	}
	if (!second) return;

	second->left = second->right = second;

	auto L = first->left;
	auto R = second->right;

	second->right = first;
	first->left = second;
	L->right = R;
	R->left = L;

}

template <class T, class Other>
void fib_heap<T, Other>::merge(fib_heap<T, Other> second) {
	if (!second.size)
		return;
	if (!size) {
		min = second.min;
		size = second.size;
		return;
	}

	union_lists(min, second->min);
	size += second.size;
	if (min->data < second.min->data) {
		min = second.min;
	}
}

template <class T, class Other>
void fib_heap<T, Other>::delete_min() {
	auto prev_min = min;
	union_lists(min, min->child);
	auto L = min->left;
	auto R = min->right;
	L->right = R;
	R->left = L;
	if (prev_min->right == prev_min) {
		return;
	}
	min = min->right;
	consolidate();
	size--;

}

template <class T, class Other>
void fib_heap<T, Other>::consolidate() {
	vector<node<T, Other> * > A(20, nullptr);

	vector<node<T, Other> *> vertexes;
	auto pointer = min;
	do {
		vertexes.push_back(pointer);
		pointer = pointer->right;
	} while (pointer != min);


	for (int i = 0; i < vertexes.size(); i++) {
		pointer = vertexes[i];
		cout << pointer << " " << i << " " << pointer->degree << endl;
		while (A[pointer->degree]) {
			cout << 2;
			auto addTo = A[pointer->degree], adding = pointer;
			A[pointer->degree] = nullptr;
			if (addTo->data > adding->data) {
				swap(addTo, adding);
			}
			union_leafs(addTo->child, adding);

			adding->parent = addTo;
			addTo->degree++;
			pointer = addTo;
		}
		A[pointer->degree] = pointer;
		cout << 3;
		pointer = pointer->right;

		for (auto el : A) {

			cout << (el == nullptr ? 0 : 1) << " ";
		}

	}

	min = nullptr;
	for (auto el : A) {
		if (el)
		{
			insert(el);
		}
		cout << (el == nullptr ? 0 : 1) << " ";
	}

}

int main() {


	vector<category>  categories;
	read_from_file("shop.txt", categories);

	//building tree
	fib_heap<double, product*> heap;



	for (int i = 1; i < categories[0].products.size(); i++) {
		heap.insert(categories[0].products[i]->price, categories[0].products[i]);
	}


	int k = 0;
	while (true) {

		if (k)return 0;

		cout << "Extract min? ";
		cout.setstate(ios_base::failbit);
		int t;
		cin >> t;
		if (t) heap.delete_min();
		else k = 1;
		ofstream fout("file.txt");
		auto * p = heap.min;
		int i = 0;

		while (p != heap.min || !i) {
			i++;

			queue<node<double, product*>* > q;

			if (p->degree == 0) {
				fout << "\"" << p->other->name << " | " << p->data << "\"-> \"" << p->other->name << " | " << p->data << "\"" << endl;
				p = p->right;
				continue;
			}
			q.push(p);

			while (!q.empty()) {

				auto tmp = q.front();
				auto tmp2 = q.front()->child;
				q.pop();
				int j = 0;
				while (tmp2 && (tmp2 != tmp->child || j == 0)) {
					j++;
					fout << "\"" << tmp->other->name << " | " << tmp->data << "\"-> \"" << tmp2->other->name << " | " << tmp2->data << "\"" << endl;
					q.push(tmp2);
					tmp2 = tmp2->right;
				}
			}
			p = p->right;
		}
		cout.setstate(ios_base::goodbit);
	}



}

