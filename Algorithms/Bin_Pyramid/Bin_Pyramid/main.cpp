#include <vector>
#include <fstream>
#include <queue>
#include <iostream>
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

template <class T, class Other>
struct node {
	T data;
	Other other;
	node *parent;
	node *child;
	int degree;
	node *brother;
	node(T data, Other other) :data(data), other(other), parent(nullptr), child(nullptr), brother(nullptr), degree(0) {}
};
template <class T, class Other>
struct bynomial_heap {
	node<T, Other> *head;
	bynomial_heap();
	void insert(T, Other);
	node<T, Other> *minimum();
	node<T, Other> *extract_minimum();
	node<T, Other> *union_heaps(bynomial_heap);
	void decrease(node<T, Other>*, T);
	void remove(node<T, Other>*);
	void bynomial_links(node<T, Other> *, node<T, Other> *);
	void heap_merge(bynomial_heap);


};




template <class T, class Other>
bynomial_heap<T, Other>::bynomial_heap() :head(nullptr) {}//конструктор для построения кучи

template <class T, class Other>
node<T, Other>* bynomial_heap<T, Other>::minimum() {//возвращает указатель на элемент кучи с минимальным ключем
	node<T, Other> * y = head;
	node<T, Other> * x = head;
	while (x) {
		if (x->data < y->data) {
			y = x;
		}
		x = x->brother;
	}
	return y;
}

template <class T, class Other>
void bynomial_heap<T, Other>::bynomial_links(node <T, Other> * y, node <T, Other> *z) {
	y->parent = z;
	y->brother = z->child;
	z->child = y;
	z->degree = z->degree + 1;
}
template <class T, class Other>
void bynomial_heap<T, Other>::heap_merge(bynomial_heap<T, Other> b) {
	if (!head) {
		head = b.head;
		return;
	}
	node<T, Other> *pointer_1 = head;
	node<T, Other> *pointer_2 = b.head;
	node <T, Other> *pointer = nullptr;//список для поинтера1 и поинтера 2
	node <T, Other> *prev = nullptr;
	node<T, Other> *new_head = nullptr;//первый элемент списка

	while (pointer_1 &&pointer_2) {
		if (pointer_1->degree <= pointer_2->degree) {
			prev = pointer;
			pointer = pointer_1;
			if (prev) {
				prev->brother = pointer;
			}
			else {
				new_head = pointer_1;
			}
			pointer_1 = pointer_1->brother;
		}
		else {
			prev = pointer;
			pointer = pointer_2;
			if (prev) {
				prev->brother = pointer;
			}
			else {
				new_head = pointer_2;
			}
			pointer_2 = pointer_2->brother;
		}
	}
	if (pointer_1) {
		pointer->brother = pointer_1;
	}
	else {
		pointer->brother = pointer_2;
	}
	head = new_head;
}

template <class T, class Other>
node<T, Other> * bynomial_heap<T, Other>::union_heaps(bynomial_heap<T, Other> b) {//объединяет две кучи и возвращает новую
	bynomial_heap h;
	heap_merge(b);
	if (!head) {
		return nullptr;
	}
	node<T, Other> *x_prev = nullptr;
	node<T, Other> *x = head;
	node<T, Other> *x_next = x->brother;
	while (x_next) {
		if (x->degree != x_next->degree || (x_next->brother && x_next->brother->degree == x->degree)) {
			x_prev = x;
			x = x_next;
		}
		else {
			if (x->data <= x_next->data) {
				x->brother = x_next->brother;
				x_next->brother = nullptr;
				bynomial_links(x_next, x);
			}
			else {
				if (!x_prev)
					head = x_next;
				else
					x_prev->brother = x_next;

				bynomial_links(x, x_next);
				x = x_next;
			}
		}
		x_next = x->brother;

	}
	return nullptr;

}
template <class T, class Other>
void bynomial_heap<T, Other>::insert(T data, Other other) {
	bynomial_heap h;
	h.head = new node<T, Other>(data, other);

	union_heaps(h);
}

template <class T, class Other>
node<T, Other> *bynomial_heap<T, Other>::extract_minimum() {//поиск минимального

	node<T, Other> *pointer = head;
	node<T, Other> *pointer_prev = nullptr;
	node<T, Other> *min = head;
	node<T, Other> *min_prev = nullptr;

	while (pointer) {
		if (pointer->data < min->data) {//нашли
			min = pointer;
			min_prev = pointer_prev;
		}
		pointer_prev = pointer;
		pointer = pointer->brother;//если нет то сдвигаем указатель на брата
	}
	if (min_prev) {
		min_prev->brother = min->brother;
	}
	else {
		head = head->brother;
	}

	bynomial_heap h;
	pointer = min->child;
	h.head = min->child;


	node<T, Other> *pointer1 = nullptr;
	node<T, Other> *pointer2 = pointer;
	node<T, Other> *pointer3 = pointer->brother;
	while (pointer2) {
		pointer2->parent = nullptr;
		pointer2->brother = pointer1;
		pointer1 = pointer2;
		pointer2 = pointer3;
		if (pointer3) {
			pointer3 = pointer3->brother;
		}

	}
	h.head = pointer1;
	union_heaps(h);
	return min;

}

int main(int argc, const char * argv[]) {

	vector<category>  categories;
	read_from_file("shop.txt", categories);

	//building tree
	bynomial_heap<double, product*> heap;



	for (int i = 1; i < categories[0].products.size(); i++) {
		heap.insert(categories[0].products[i]->price, categories[0].products[i]);
	}

	ofstream fout("file.txt");
	heap.extract_minimum();
	heap.extract_minimum();
	heap.extract_minimum();
	node<double, product*> * p = heap.head;
	int i = 0;
	while (p) {


		queue<node<double, product*>* > q;
		q.push(p);

		while (!q.empty()) {
			node<double, product*>* tmp = q.front();
			node<double, product*>* tmp2 = q.front()->child;
			q.pop();

			while (tmp2) {
				fout << "\"" << tmp->other->name << " | " << tmp->data << "\"-> \"" << tmp2->other->name << " | " << tmp2->data << "\"" << endl;
				q.push(tmp2);
				tmp2 = tmp2->brother;
			}
		}
		p = p->brother;
	}



	return 0;
}
