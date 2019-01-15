#include "expression.h"

bool Expression :: is_letter(int ascii_pos) {
	  return ascii_pos >= 65 && ascii_pos <= 90 || 
			 ascii_pos >= 97 && ascii_pos <= 122;
}
