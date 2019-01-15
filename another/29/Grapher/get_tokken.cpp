#include "expression.h"

string Expression :: get_token(const string &s, int &pos) {
	string token = "";
	while (pos < s.size() && s[pos] == ' ') {
		   pos++;
	}
	if (pos == s.size()) {
		token = "";
	} else if (s[pos] == '(' || s[pos] == ')') {
	    token += s[pos];
	    pos++;
	} else if (is_digit((int)s[pos]) || is_letter((int)s[pos])) {
		while (pos < s.size() && (is_digit((int)s[pos]) || is_letter((int)s[pos]))) {
			   token += s[pos];
			   pos++;
		}
	} else {
		while (pos < s.size() && s[pos] != ' ' && s[pos] != '(' && s[pos] != ')' &&
		       !(is_digit((int)s[pos]) || is_letter((int)s[pos]))) {
			   token += s[pos];
			   pos++;
		}
	}
	return token;
}
