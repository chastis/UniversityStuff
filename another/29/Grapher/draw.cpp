#include "expression.h"
#include "coordinate_system.h"

void draw() {
	Coordinate_system cs(8);
	cs.draw_system();
	
	getch();
}
