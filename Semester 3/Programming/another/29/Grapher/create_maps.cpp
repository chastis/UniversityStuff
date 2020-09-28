#include "expression.h"

map <string, const int> create_operators_map() {
	map <string, const int> operators_identifiers;
	operators_identifiers.insert(pair <string, const int>("|+",  0));
	operators_identifiers.insert(pair <string, const int>("|-",  1));
	operators_identifiers.insert(pair <string, const int>("||+", 2));
	operators_identifiers.insert(pair <string, const int>("||-", 3));
	operators_identifiers.insert(pair <string, const int>("*",   4));
	operators_identifiers.insert(pair <string, const int>("/",   5));
	return operators_identifiers;
}
map <string, const int> create_functions_map() {
	map <string, const int> functions_identifiers;
	functions_identifiers.insert(pair <string, const int>("exp", 0));
	return functions_identifiers;
}
map <string, const int> operators_identifiers = create_operators_map();
map <string, const int> functions_identifiers = create_functions_map();
