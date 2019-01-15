#ifndef L_SYSTEM
#define L_SYSTEM

#include "turtle.h"
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

typedef void (*TurtleFunc) (Turtle&, int);

class LSystem {
	
	private:
		string axiom;
		vector <char> alphabet;
		vector <string> rules;
		vector <TurtleFunc> interpretation;
		float x, y, a;
		int maxX, maxY;
		
		string generateNext(string predGen);
		void drawGen(string gen, int numOfGen);
		
	public:
		LSystem(string, vector <char>, vector <string>, vector <TurtleFunc>,
			float, float, float, int, int);
		string generate(int generation);
		void generate(int targetGeneration, int ms);
		void generateInf(int ms);
};

#endif // L_SYSTEM
