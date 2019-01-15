#include "expression.h"

bool Expression :: shunting_yard_algorithm(string input_string) {
	 string output_string = "", cur_token;
	 vector <string> stack;
	 bool error = false;
	 for (int i = 0; !error; ) {
	 	  cur_token = get_token(input_string, i);
	 	  if (cur_token == "") {
	 	  	  break;
		  } else if (cur_token == "+" || cur_token == "-") {
		  	  cur_token = "|" + cur_token;
		  }
	 	  switch (type_of_token(cur_token)) {
	 	  	case NUMBER : {
	 	  		output_string += cur_token + " ";
				break;
			}
			case VARIABLE : {
	 	  		output_string += cur_token + " ";
	 	  		if (variables.find(cur_token) == variables.end()) {
	 	  			variables.insert(make_pair(cur_token, 0));
				}
				break;
			}
			case OPERATOR : {
				if (cur_token == "|+" || cur_token == "|-") {
					int arity = find_arity(output_string, stack);
					if (arity == 2) {
					  	cur_token = "|" + cur_token;
					}
				}
				while (!stack.empty() && 
				       type_of_token(stack.back()) == OPERATOR &&
				       priorities[operators_identifiers[stack.back()]] <=  
					   priorities[operators_identifiers[cur_token]]) {
					output_string += stack.back() + " ";
					stack.pop_back();
				}
				stack.push_back(cur_token);
				break;
			}
			case FUNCTION : {
				stack.push_back(cur_token);
				break;
			}
			case OPENING_BRACKET : {
				stack.push_back(cur_token);
				break;
			}
			case CLOSING_BRACKET : {
				while (!stack.empty() &&
				       type_of_token(stack.back()) != OPENING_BRACKET) {
					output_string += stack.back() + " ";
					stack.pop_back();
				}
				if (stack.empty()) {
					error = true;
					break;
				} else {
					stack.pop_back();
					if (!stack.empty() && type_of_token(stack.back()) == FUNCTION) {
						output_string += stack.back() + " ";
						stack.pop_back();
					}
				}
				break;
			}
			case UNKNOWN : {
				error = true;
				break;
			}
		  } 
	 }
	 while (!stack.empty()) {
	 	if (type_of_token(stack.back()) == OPENING_BRACKET) {
	 		error = true;
	 		break;
		}
	 	output_string += stack.back() + " ";
		stack.pop_back();
	 }
	 reverse_polish_notation = output_string;
	 return error;
}
