#include "expression.h"

bool Expression :: is_digit(int ascii_pos) {
	 return ascii_pos >= 48 && ascii_pos <= 57;
}
