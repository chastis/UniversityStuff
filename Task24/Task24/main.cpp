#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <set>
#include <map>
#include <string>
#include <vector>
using namespace std;
//map <char, int> ::iterator id1,id2;
struct all
{
	char letter;
	int cout;
	string kod;
};
struct branch
{
	int number;
	char letter;
	int count;
	vector <int> kids;
};
int write(vector  < all > i_am_vector) {
	for (auto now : i_am_vector) {
		cout << now.letter << ": " << now.kod << endl;
	}
	return 0;
}
int write_tree(vector <branch> tree) {
	for (auto now : tree) {
		cout << now.number << " " << now.letter << " " << now.count << " kids: ";
		for (auto now2 : now.kids) {
			cout << now2 << " ";
		}
		cout << endl;
	}
	return 0;
}
bool staff(all a, all b) {

	return a.cout<b.cout;
}
int oh_my_God(int kid1, int kid2, vector <branch> leaves, vector  < all > &i_am_vector, string kod) {
	for (int i = 0; i < leaves.size(); i++) {
		if (kid1 == leaves[i].number) {
			if (leaves[i].letter == '$') {
				//cout << "rec " << leaves[i].kids[0] << leaves[i].kids[1] << kod + "0" << endl;
				oh_my_God(leaves[i].kids[0], leaves[i].kids[1], leaves, i_am_vector, kod + "0");

			}
			else {
				for (int j = 0; j < i_am_vector.size(); j++) {
					if (i_am_vector[j].letter == leaves[i].letter) {
						i_am_vector[j].kod = kod + '0';
					}
				}
			}

		}
		else
			if (kid2 == leaves[i].number) {
				if (leaves[i].letter == '$') {
					oh_my_God(leaves[i].kids[0], leaves[i].kids[1], leaves, i_am_vector, kod + "1");
				}
				else {
					for (int j = 0; j < i_am_vector.size(); j++) {
						if (i_am_vector[j].letter == leaves[i].letter) {
							i_am_vector[j].kod = kod + '1';
						}
					}
				}

			}
	}
	return 0;
}
int main() { ///////////////////////////////////////////////////////begin
	string s;
	getline(cin, s);
	map  <char, int >  symbols;
	vector < all > i_am_vector;
	for (int i = 0; i < s.size(); i++) {
		if (symbols.find(s[i]) == symbols.end()) {
			symbols[s[i]] = 1;
		}
		else {
			symbols[s[i]] ++;
		}
	}
	for (auto now : symbols) {
		all temp_all;
		temp_all.letter = now.first;
		temp_all.cout = now.second;
		temp_all.kod = "";
		i_am_vector.push_back(temp_all);
	}

	sort(i_am_vector.begin(), i_am_vector.end(), staff);
	//write(i_am_vector);

	//High wey to hell////////////////////////////////////////

	vector <branch> tree, leaves;

	for (int i = 0; i < i_am_vector.size(); i++) {
		branch temp;
		temp.number = i;
		temp.letter = i_am_vector[i].letter;
		temp.count = i_am_vector[i].cout;
		tree.push_back(temp);
	}
	//cout << "tree 1 " << endl;
	//write_tree(tree);
	int k = i_am_vector.size();
	while (tree.size() != 1) {
		branch temp;
		leaves.push_back(tree[0]);
		leaves.push_back(tree[1]);

		temp.count = tree[0].count + tree[1].count;
		temp.letter = '$';
		temp.number = k;
		temp.kids.push_back(tree[0].number);
		temp.kids.push_back(tree[1].number);

		int ij = 0;
		bool bl = true;
		while (ij < tree.size() && bl) {
			if (temp.count <= tree[ij].count) {
				tree.insert(tree.begin() + ij, temp);
				bl = false;
			}
			ij++;

		}
		if (bl) {
			tree.push_back(temp);
		}
		k = k + 1;
		tree.erase(tree.begin());
		tree.erase(tree.begin());

		//cout << "tree 2 " << endl;
		//write_tree(tree);

		//cout << "leaves 1 " << endl;
		//write_tree(leaves);
	}
	//cout << "tree 3 " << endl;
	//write_tree(tree);

	//cout << "leaves 4 " << endl;
	//write_tree(leaves);
	//recursion///////////////////////////////////////////////////////
	if (tree[0].kids.size() > 0) { oh_my_God(tree[0].kids[0], tree[0].kids[1], leaves, i_am_vector, ""); }
	else {
		i_am_vector[0].kod = '0';
	}
	//cout << "i_am_vector " << endl;
	//write(i_am_vector);
	/////////////////////////////////////////////////////////
	int sum = 0;
	for (int i = 0; i < i_am_vector.size(); i++) {
		sum = sum + i_am_vector[i].cout*i_am_vector[i].kod.size();
	}
	//cout << "Hello!" << endl;
	cout << i_am_vector.size() << " " << sum << endl;
	write(i_am_vector);
	for (int i = 0; i < s.size(); i++) {
		bool bl = true;
		int j = 0;
		while (bl) {
			if (i_am_vector[j].letter == s[i]) {
				cout << i_am_vector[j].kod;
				bl = false;
			}
			j = j + 1;
		}

	}
	cout << endl << "That's all Folks!" << endl;
	cin.get();
	return 0;
}
//код написаный в 2016 году