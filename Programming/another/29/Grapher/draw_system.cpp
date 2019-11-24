#include "coordinate_system.h"

void Coordinate_system :: draw_system() {
	setfillstyle(1, WHITE);
	bar(0, 0, max_x, max_y);
	
	setcolor(BLACK);
	line(max_x / 2, border, max_x / 2, max_y - border);
	line(border, max_y / 2, max_x - border, max_y / 2);
	int triangle_1[6];
	triangle_1[0] = max_x / 2;
	triangle_1[1] = border;
	triangle_1[2] = max_x / 2 + arrow_width;
	triangle_1[3] = arrow_height + border;
	triangle_1[4] = max_x / 2 - arrow_width;
	triangle_1[5] = arrow_height + border;
	setfillstyle(1, RED);
	fillpoly(3, triangle_1);
	int triangle_2[6];
	triangle_2[0] = max_x - border;
	triangle_2[1] = max_y / 2;
	triangle_2[2] = max_x - arrow_height - border;
	triangle_2[3] = max_y / 2 + arrow_width;
	triangle_2[4] = max_x - arrow_height - border;
	triangle_2[5] = max_y / 2  - arrow_width;
	fillpoly(3, triangle_2);
	
	for (int x = -range; x <= range; x++) {
		 if (x != 0) {
			 setcolor(LIGHTGRAY);
			 line( max_x / 2 + step * x, max_y / 2 - (max_y / 2 - border), max_x / 2 + step * x, max_y / 2 + stroke_size + (max_y / 2 - border) );
			 setcolor(BLACK);
			 line( max_x / 2 + step * x, max_y / 2 - stroke_size, max_x / 2 + step * x, max_y / 2 + stroke_size );
		}
	}
	for (int y = -range; y <= range; y++) {
		 if (y != 0) {
			 setcolor(LIGHTGRAY);
			 line( max_x / 2 - (max_y / 2 - border), max_y / 2 + step * y, max_x / 2 + (max_y / 2 - border), max_y / 2 + step * y );
			 setcolor(BLACK);
			 line( max_x / 2 - stroke_size, max_y / 2 + step * y, max_x / 2 + stroke_size, max_y / 2 + step * y );
		}
		 
	}
}


