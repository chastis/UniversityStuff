#include "expression.h"
#include "coordinate_system.h"
#include <iostream>

using namespace std;

Coordinate_system cs(10);
Expression func;

float f(float);
void run_interface();

int main() {
	initwindow(max_x, max_y);
	cs.draw_system();
	run_interface();
	
	getch();
}

float f(float x) {
	func.variables["x"] = x;
	pair <float, bool> result = func.calculate();
	
	return result.first;
}

void run_interface() {
	cout << "This programm for drawing functions" << endl << endl;
	int choose = 1;
	do {
		cout << endl;
		cout << "-------------------------" << endl;
		cout << "           Menu" << endl;
		cout << "close system        - 0" << endl;
		cout << "clear system        - 1" << endl;
		cout << "add function        - 2" << endl;
		cout << "show functions list - 3" << endl;
		cout << "delete function     - 4" << endl;
		cout << "-------------------------" << endl << endl;;
		cin >> choose;
		switch (choose) {
			case 1 : {
				cs.functions.clear();
				cs.draw_system();
				break;
			}
			case 2 : {
				string str_function;
				int color;
				cout << endl << "Enter a function: " << endl;
				cin.ignore();
				getline(cin, str_function);
				cout << "Enter a color from this: " << endl;
				cout << "(BLACK    - 0,  BLUE         - 1,  GREEN      - 2,  CYAN       - 3, " << endl;
				cout << " RED      - 4,  MAGENTA      - 5,  BROWN      - 6,  LIGHTGRAY  - 7, " << endl;
				cout << " DARKGRAY - 8,  LIGHTBLUE    - 9,  LIGHTGREEN - 10, LIGHTCYAN  - 11, " << endl;
                cout << " LIGHTRED - 12, LIGHTMAGENTA - 13, YELLOW     - 14, WHITE      - 15):" << endl;
				cin >> color;
				cs.functions.push_back(make_pair(str_function, color));
				func.shunting_yard_algorithm(cs.functions.back().first); 
				cs.draw_function(f, color); 
				break;
			}
			case 3 : {
				cout << endl << "Functions list:" << endl;
				for (int i = 0; i < cs.functions.size(); i++) {
		 			 cout << "N" << i << ": " << cs.functions[i].first << endl;
				}
				cout << endl;
				break;
			}
			case 4 : {
				int n;
				cout << endl << "Enter number of function which you want to delete:" << endl;
				cin >> n;
				for (int i = n + 1; i < cs.functions.size(); i++) {
					 cs.functions[i - 1] = cs.functions[i];
					 cs.functions.pop_back();
				}
				cs.draw_system();
				for (int i = 0; i < cs.functions.size(); i++) {
		 			 func.shunting_yard_algorithm(cs.functions[i].first);
		 			 cs.draw_function(f, cs.functions[i].second);
				}
				break;
			}
			default : {
				break;
			}
		}
		bool next = false;
		while (!next) {
			if (ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_RBUTTONDOWN)) {
				if (ismouseclick(WM_LBUTTONDOWN)) { 
					cs.range++;
				} else {
					cs.range--;
				}
				cs.step = (max_y / 2 - border - 2 * arrow_height) / cs.range;
				cs.draw_system();
				for (int i = 0; i < cs.functions.size(); i++) {
		 			 func.shunting_yard_algorithm(cs.functions[i].first);
		 		 	cs.draw_function(f, cs.functions[i].second);
				}
				clearmouseclick(WM_LBUTTONDOWN);
          		clearmouseclick(WM_RBUTTONDOWN);
			}
			next = kbhit();
		}
		getch();
	} while (choose != 0);
}

