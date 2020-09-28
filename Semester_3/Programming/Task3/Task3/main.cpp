#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
using namespace std;
struct Node
{
	Node()
	{
		up = NULL;
		down = NULL;
	};
	Node(char a)
	{
		edge = a;
		up = NULL;
		down = NULL;
	}
	char edge;
	Node * up;
	Node * down;
};

void print(Node * head) {
	if (head->down) print(head->down);
	cout << head->edge << " ";
	if (head->up) print(head->up);
}
int main()
{
	cout << "Entered the line, where 'F' mean bend to FORWARD and 'B' mean bend to BACK" << endl;
	string s;
	vector<Node *> pointers; //указатели на элементы на определенном этаже графа
	getline(cin, s);
	Node * head = new Node;
	//head->edge = (s[0] == 'F' ? 'F' : 'T');
	pointers.push_back(head);
	//создаем граф степени 2
	//в зависимости от изиба предка - дети могут иметь либо ТФ ребра, либо ФТ
	//создаем граф а потом рекурсивно выводим
	//граф для FBBF
	//       F
	//   T       F
	// T   F   T   F
	//F T F T F T F T
	for (int j = 0; j < s.size(); j++) 
	{
		char c = s[j];
		bool flag = (c == 'B' ? true : false);
		//fill chilgren
		for (auto p : pointers) {
			//to us/from us
			p->edge = (flag ? 'T' : 'F');
			flag = !flag;
		}
		if (j == s.size()-1) break;

		int n = pointers.size();
		//make children
		for (int i = 0; i < n; i++) {
			Node * temp = new Node;
			pointers[0]->down = temp;
			pointers.push_back(pointers[0]->down);
			temp = new Node;
			pointers[0]->up = temp;
			pointers.push_back(pointers[0]->up);
			temp = pointers[0];
			pointers.erase(pointers.begin());
		}
	}
	cout << "Answer: ";
	print(head);
	cout << endl << "That's all Folks!" << endl;
	_getch();
	return 0;
}