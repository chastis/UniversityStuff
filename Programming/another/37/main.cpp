#include <iostream>
#include <fstream>
#include <cmath>
#include <graphics.h>
#include <ctime>
#include "l_system.h"

using namespace std;

const string ALPHABET = "F+-[]X";
string FILENAME = "tree.txt";
const int MAXX = 500, MAXY = 500;
const float X = 250, Y = 450, A = M_PI / 2;

void f0(Turtle& t, int g) {
	t.forward(/*pow(2.0, -g) * 100*/ 3);
}

void f1(Turtle& t, int g) {
	t.rotate(20);
}

void f2(Turtle& t, int g) {
	t.rotate(-20);
}

void f3(Turtle& t, int g) {
	//
}

void f4(Turtle& t, int g) {
	//
}

void f5(Turtle& t, int g) {
	//
}


int main() {
	ifstream fin(FILENAME.c_str());
	int n;
	fin >> n;
	string axiom;
	fin >> axiom;
	vector <char> alphabet;
	vector <string> rules(ALPHABET.size());
	for (int i = 0; i < ALPHABET.size(); i++) {
		alphabet.push_back(ALPHABET[i]);
		fin >> rules[i];
	}
	vector <TurtleFunc> tf;
	tf.push_back(f0);
	tf.push_back(f1);
	tf.push_back(f2);
	tf.push_back(f3);
	tf.push_back(f4);
	tf.push_back(f5);
	
	srand(time(NULL));
	LSystem lSystem(axiom, alphabet, rules, tf, X, Y, A, MAXX, MAXY);
	//cout << lSystem.generate(n) << endl;
	//lSystem.generate(n);
	lSystem.generate(n, 1000);
}
