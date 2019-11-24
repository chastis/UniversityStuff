#include "l_system.h"
#include <graphics.h>

LSystem :: LSystem(string axiom, vector <char> alphabet, vector <string> rules, 
	vector <TurtleFunc> interpretation, float x, float y, float a, int maxX, int maxY):
	axiom(axiom), alphabet(alphabet), rules(rules),
	interpretation(interpretation), x(x), y(y), a(a), maxX(maxX), maxY(maxY) {
	initwindow(maxX, maxY);
}

string LSystem :: generateNext(string predGen) {
	string nextGen = "";
	for (int i = 0; i < predGen.size(); i++) {
		for (int j = 0; j < alphabet.size(); j++) {
			if (alphabet[j] == predGen[i]) {
				nextGen += rules[j];
				break;
			}
		}
	}
	return nextGen;
}

void LSystem :: drawGen(string g, int numOfGen) {
	Turtle t(x, y, a);
	vector <Turtle> st;
	setfillstyle(1, WHITE);
	bar(0, 0, maxX, maxY);
	setcolor(BLACK);
	for (int i = 0; i < g.size(); i++) {
		if (g[i] == '[') {
			st.push_back(t);
			continue;
		} else if (g[i] == ']') {
			t = st[st.size() - 1];
			st.pop_back();
			continue;
		}
		for (int j = 0; j < alphabet.size(); j++) {
			if (alphabet[j] == g[i]) {
				float sx = t.getX(), sy = t.getY();
				interpretation[j](t, numOfGen);
				line(sx,  sy, t.getX(), t.getY());
			} 
		}
	}
}

string LSystem :: generate(int g) {
	string s = axiom; 
	for (int i = 0; i < g; i++) {
		s = generateNext(s);
	}
	drawGen(s, g);
	getch();
	return s;
}

void LSystem :: generate(int g, int ms) {
	string s = axiom; 
	drawGen(s, 0);
	for (int i = 1; i <= g; i++) {
		delay(ms);
		s = generateNext(s);
		drawGen(s, i);
	}
	getch();
}

void LSystem :: generateInf(int ms) {
	string s = axiom; 
	drawGen(s, 0);
	int i = 0;
	while (true) {
		delay(ms);
		s = generateNext(s);
		drawGen(s, ++i);
	}
}
