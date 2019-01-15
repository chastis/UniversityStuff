#include "coordinate_system.h"

int Coordinate_system :: find_y(float f(float), int coordinate_x) {
	float x = (float)(coordinate_x - max_x / 2) / step;
	float y = f(x);
	int coordinate_y = max_y / 2 - (int) (y * step);
	
	return coordinate_y;
}
