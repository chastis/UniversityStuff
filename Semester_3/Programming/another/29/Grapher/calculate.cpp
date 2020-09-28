#include "expression.h"
#include <cstdlib>

pair <float, bool> Expression :: calculate() {
	vector <float> stack;
	string cur_token;
	bool error = false;
	float value;
	for (int i = 0; !error; ) {
		 cur_token = get_token(reverse_polish_notation, i);
		 if (cur_token == "") {
		 	 break;
		 }
		 switch (type_of_token(cur_token)) {
		 	case NUMBER : {
		 		stack.push_back(atoi(cur_token.c_str())); 
				break;
			}
			case VARIABLE : {
				stack.push_back(variables[cur_token]);
				break;
			}
			case OPERATOR : {
				 switch (operators_arities[operators_identifiers[cur_token]]) {
				 	case 1 : {
				 		if (stack.empty()) {
				 			error = true;
				 			break;
						}
				 		switch (operators_identifiers[cur_token]) {
				 			case UNARY_PLUS : {
				 				value = unary_plus(stack[stack.size() - 1]);
								break;
							}
							case UNARY_MINUS : {
								value = unary_minus(stack[stack.size() - 1]);
								break;
							}
						}
						break;
					}
					case 2 : {
						if (stack.size() < 2) {
				 			error = true;
				 			break;
						}
				 		switch (operators_identifiers[cur_token]) {
				 			case BINARY_PLUS : {
				 				value = binary_plus(stack[stack.size() - 2], 
								                    stack[stack.size() - 1]);
								break;
							}
							case BINARY_MINUS : {
								value = binary_minus(stack[stack.size() - 2], 
								                     stack[stack.size() - 1]);
								break;
							}
							case MULTIPLICATION : {
								value = multiplication(stack[stack.size() - 2], 
								                       stack[stack.size() - 1]);
								break;
							}
							case DIVISION : {
								value = division(stack[stack.size() - 2], 
								                 stack[stack.size() - 1]);
								break;
							}
						}
						break;
					}
				 }
				for (int j = 0; j < operators_arities[operators_identifiers[cur_token]]; j++) {
					 stack.pop_back();
				}
				stack.push_back(value);
				break;
			}
			case FUNCTION : {
				switch (functions_arities[functions_identifiers[cur_token]]) {
					case 1 : {
						if (stack.empty()) {
				 			error = true;
				 			break;
						}
						switch (functions_identifiers[cur_token]) {
							case EXPONENT : {
								value = exponent(stack[stack.size() - 1]);
								break;
							}
						}
						break;
					}
				}
				for (int j = 0; j < functions_arities[functions_identifiers[cur_token]]; j++) {
					 stack.pop_back();
				}
				stack.push_back(value);
				break;
			}
		 }
	}
	if (stack.size() != 1) {
		error = true;
	}
	return make_pair(stack.back(), error);	
}
