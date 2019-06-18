#include <iostream>
#include <algorithm>
#include "Bplus.h"
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
		cout << categories[i].name << " " << n << endl;
		categories[i].products.resize(n);
		for (int j = 0; j<n; j++) {

			categories[i].products[j] = new product;
			getline(fin, categories[i].products[j]->name);
			categories[i].products[j]->type = &categories[i];
			categories[i].products[j]->price = (int)(rand() % 1000 + 1) / 100.;//price
			cout << categories[i].products[j]->name << endl;
		}
	}

	fin.close();

}

int main() {
	BPlusTree<double, string> tree(2);

	vector<category>  categories;
	read_from_file("shop.txt", categories);

	//building tree

	random_shuffle(categories[0].products.begin(), categories[0].products.end());
	for (int i = 1; i < 10; i++) {
		tree.insert(categories[0].products[i]->price, categories[0].products[i]->name);

	}
	tree.insert(5.15, "Bohemian");
	tree.insert(7.15, "Prapsody");
	tree.writeToFile("data.out");

	return 0;
}


