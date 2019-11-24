#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <conio.h>

using namespace std;

int main() {
	string a, b;
	getline(cin, a);
	getline(cin, b);
	map<char, int> map_a, map_b;
	//char and amount of this char
	for (auto ch : a) {
		map_a[ch]++;
	}
	for (auto ch : b) {
		map_b[ch]++;
	}
	string answer = "";
	//comapre between a and b
	for (auto ch : map_a) {
		//minimum of current char in a and b
		int min_ch = min(ch.second, map_b[ch.first]);
		for (int i = 0; i < min_ch; i++) answer += ch.first;
	}
	cout << answer << endl;
	cout << "That's all Folks!" << endl;
	_getch();
	return 0;
}