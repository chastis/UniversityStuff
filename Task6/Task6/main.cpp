#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;
enum coins_side {HEAD, TAIL};
struct Possibilities {
	coins_side side;
	//tails(m)
	Possibilities * right;
	//heads(n)
	Possibilities * left;
};
//build tree of possibilities
//it will return true if we find answer
bool build_possibilities(Possibilities* & arrangment, vector<bool> & coins, vector<coins_side> & answer, int n, int m, int l, int step) {
	if (n == 0 && m == 0 && l == 0) return true;
	if (l < 0) return false;
	//head
	if (n > 0) {
		Possibilities * left = new Possibilities;
		left->side = coins[step] ? TAIL : HEAD;
		arrangment->left = left;
		answer.push_back(HEAD);
		if (build_possibilities(left, coins, answer, n - 1, m, coins[step] ? l : l - 1, step + 1)) return true;
		answer.pop_back();
	}
	//tail
	if (m > 0) {
		Possibilities * right = new Possibilities;
		right->side = coins[step] ? HEAD : TAIL;
		arrangment->right = right;
		answer.push_back(TAIL);
		if (build_possibilities(right, coins, answer, n, m - 1, coins[step] ? l - 1 : l, step + 1)) return true;
		answer.pop_back();
	}
	return false;
}
int main() {
	//По колу розміщено N монет гербами вгору і M монет гербами вниз.
	//Обходячи коло по ходу годинникової стрілки, перевертається кожна S - та монета.
	//У перший раз рахунок починається з герба.У якому порядку потрібно розставити монети, щоб після K ходів стало L монет, що лежать гербами вгору.
	int n, m, s, k, l;
	//n is amount of head;
	//m is amount of tails;

	//l is amount of head in the end;
	cin >> n >> m >> s >> k >> l;
	//array with answer of question: did flip coin or not?
	vector<bool> coins(n + m);
	coins.assign(n + m, false);
	int pos = 0, flip = k, i = 0;
	while (flip > 0) {
		if (pos == n + m) pos = 0;
		if (i != 0 && i % s == 0) {
			coins[pos] = !coins[pos];
			flip--;
		}
		i++;
		pos++;
	}
	//arrangment - расположение
	//top vertex of tree of possibilities
	//value of each vertex is Head/Tail
	//depending on what, we have after all coins flip
	//left child is branch with head
	//right - with tail
	//we will get tree, like that
	//          T/H
	//     H/T            T/H
	//H/T        T/H    H/T      T/H
	//depending we did flip coin or not
	Possibilities * arrangement = new Possibilities;
	vector<coins_side> answer;
	arrangement->side = coins[0] ? TAIL : HEAD;
	int temp_n = n, temp_m = m, temp_l = l;
	if (!coins[0]) temp_l--;
	if (coins[0]) temp_m--; else temp_n--;
	answer.push_back(HEAD);

	if (build_possibilities(arrangement, coins, answer, temp_n, temp_m, temp_l, 1)) {
		for (auto now : answer) cout << ((now == TAIL) ? "TAIL " : "HEAD ");
	}
	else {
		cout << "Impossible!";
	}
	cout << endl << "That's all Folks!" << endl;
	_getch();
	return 0;
}