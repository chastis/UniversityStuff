#include "expression.h"

Tokens Expression :: type_of_token(const string &token) {
	if (token == "(") {
		return OPENING_BRACKET;
	} else if (token == ")") {
		return CLOSING_BRACKET;
	} else if ((int)token[0] <= 57 && (int)token[0] >= 49) {
		bool error = false;
		for (int i = 0; i < token.size(); i++) {
			 if (!is_digit((int)token[i])) {
			 	 error = true;
			 	 break;
			 }
		}
		if (error) {
		 	return UNKNOWN;
		} else {
			return NUMBER;
		}
	} else if (token == "0") {
		return NUMBER;
	} else if (functions_identifiers.find(token) != functions_identifiers.end()) {
		return FUNCTION;
	} else if (is_letter((int)token[0])) {
		return VARIABLE;
	} else if (operators_identifiers.find(token) != operators_identifiers.end()) {
		return OPERATOR;
	} else {
		return UNKNOWN;
	}
}
