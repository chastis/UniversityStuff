#include "expression.h"

int Expression :: find_arity(const string &output_string, const vector <string> &stack) {
	if (output_string.empty()) {
		return 1;
	} else if (!stack.empty() && stack.back() == "(") {
		int pos = output_string.size() - 2;
		while (pos >= 0 && output_string[pos] != ' ') {
			pos--;
		}
		Tokens type_of_last_token = type_of_token(output_string.substr(pos + 1, output_string.size() - pos - 2));
		if (type_of_last_token == OPERATOR || type_of_last_token == FUNCTION) {
			return 1;
		}
	} 
	return 2;
}
