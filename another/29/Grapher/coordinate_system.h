#ifndef COORDINATE_SYSTEM_H
#define COORDINATE_SYSTEM_H

#include <graphics.h>
#include <vector>
#include <utility>

const int max_x = 700, max_y = 700, 
	      arrow_width = 4, arrow_height = 12, 
		  border = 10,  stroke_size = 5;

class Coordinate_system {
	int range;
	int step;
	int find_y(float f(float), int x);
	std :: vector < std :: pair <std :: string, int> > functions;
	friend void run_interface();
	public:
		Coordinate_system(int range) : range(range) { 
		    this -> range = range;
			step = (max_y / 2 - border - 2 * arrow_height) / range; 
		}
		void draw_system();
		void draw_function(float f(float), int color);
};

#endif //COORDINATE_SYSTEM_H
