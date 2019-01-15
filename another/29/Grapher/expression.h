#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <map>
#include <string>

using namespace std;

enum Operators { 
	UNARY_PLUS,
	UNARY_MINUS,
	BINARY_PLUS,
	BINARY_MINUS,
	MULTIPLICATION,
	DIVISION
};

enum Functions { 
	EXPONENT
};

enum Tokens { 
	UNKNOWN,
	NUMBER,
	VARIABLE,
	OPERATOR,
	FUNCTION,
	OPENING_BRACKET,
	CLOSING_BRACKET
};

const int priorities[6] = {1, 1, 3, 3, 2, 2},
          operators_arities[6] = {1, 1, 2, 2, 2, 2},
          functions_arities[1] = {1};

map <string, const int> create_operators_map();
map <string, const int> create_functions_map();
extern map <string, const int> operators_identifiers;
extern map <string, const int> functions_identifiers;

class Expression {
	private:
		string reverse_polish_notation;
		map <string, float> variables;
		bool is_digit(int);
		bool is_letter(int);
		string get_token(const string&, int&);
		Tokens type_of_token(const string&);
		int find_arity(const string&, const vector <string>&);
		float unary_plus(float);
		float unary_minus(float);
		float binary_plus(float, float);
		float binary_minus(float, float);
		float multiplication(float, float);
		float division(float, float);
		float exponent(float);
		friend float f(float);
	public:
		bool shunting_yard_algorithm(string);
		pair <float, bool> calculate();
		void clear();
};

#endif //EXPRESSION_H
