#include "coordinate_system.h"

void Coordinate_system :: draw_function(float f(float), int color) {
	setcolor(color);
	int pred_x = max_x / 2 - step * range, pred_y = find_y(f, pred_x), cur_x, cur_y;
	for (cur_x = max_x / 2 - step * range + 1; cur_x <= max_x / 2 + step * range; cur_x++) {
		 cur_y = find_y(f, cur_x);
		 if (max_x / 2 - step * range <= pred_y && pred_y  <= max_x / 2 + step * range &&
		     max_x / 2 - step * range <= cur_y  && pred_y  <= max_x / 2 + step * range) {
		     line(pred_x, pred_y, cur_x, cur_y);
		 }
		 pred_x = cur_x;
		 pred_y = cur_y;
	}
}
