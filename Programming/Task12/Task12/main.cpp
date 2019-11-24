#include <iostream>

using namespace std;

struct columns {
	int data;
	int column_number;
	columns* next;
	columns* prev;
	columns() : next(nullptr) {}
	columns(int data, int column) : column_number(column), data(data), next(nullptr), prev(nullptr) {}
	void del() {
		if (prev)
			prev->next = next;
		if (next) {
			next->prev = prev;
		}
		delete this;
		return;
	}
};

struct rows {
	int row_number;
	columns *column;
	rows *next_row;
	rows() : next_row(nullptr), column(nullptr) {}
	rows(int row_num, columns* column = nullptr) : row_number(row_num), column(column), next_row(nullptr) {}

	void push_front(int data, int col) {
		columns* new_el = new columns(data, col);
		new_el->next = column;
		if (column) {
			column->prev = new_el;
		}
		column = new_el;
		return;
	}

	void push_back(int data, int col) {
		columns* new_el = new columns(data, col);
		columns* pointer = column;
		if (!pointer) {
			column = new_el;
			return;
		}
		while (pointer->next) {
			pointer = pointer->next;
		}

		new_el->prev = pointer;
		pointer->next = new_el;

		return;
	}
};

struct compressed_matrix {
	int size_x, size_y;
	rows* first_row;

	compressed_matrix() : first_row(nullptr) {}
	compressed_matrix(int size_x, int size_y) : size_x(size_x), size_y(size_y), first_row(nullptr) {}

	void read_matrix() {
		rows * pointer = first_row;
		cout << "Enter size of the matrix:" << endl;
		cin >> size_x;
		size_y = size_x;
		for (int i = 0; i < size_x; ++i) {
			for (int j = 0; j < size_y; ++j) {
				int tmp;
				cin >> tmp;
				if (tmp) {
					if (!pointer || pointer->row_number != i) {
						rows*new_row = new rows(i);
						if (pointer)pointer->next_row = new_row;
						else {
							first_row = new_row;
						}
						pointer = new_row;

					}
					pointer->push_back(tmp, j);
				}
			}
		}
	}

	void print_matrix() {
		rows* pointer = first_row;
		int prev_number = -1;
		while (pointer) {
			while (pointer->row_number - prev_number > 1) {
				for (int i = 0; i < size_x; ++i) {
					cout << 0 << " ";
				}
				cout << endl;
				prev_number++;
			}
			columns * pointer_col = pointer->column;
			int prev_column_number = -1;
			while (pointer_col) {
				while (pointer_col->column_number - prev_column_number > 1) {
					cout << "0 ";
					prev_column_number++;
				}
				cout << pointer_col->data << " ";
				prev_column_number = pointer_col->column_number;
				pointer_col = pointer_col->next;
			}
			while (size_x - prev_column_number > 1) {
				cout << "0 ";
				prev_column_number++;
			}
			prev_number = pointer->row_number;
			pointer = pointer->next_row;
			cout << endl;

		}
		while (size_y - prev_number > 1) {
			for (int i = 0; i < size_x; ++i) {
				cout << 0 << " ";
			}
			prev_number++;
			cout << endl;
		}
	}

	void push_row(int row_num, columns* column = nullptr) {
		rows* new_el = new rows(row_num, column);
		rows* pointer = first_row;
		if (!pointer) {
			first_row = new_el;
			return;
		}
		while (pointer->next_row) {
			pointer = pointer->next_row;
		}

		pointer->next_row = new_el;

		return;
	}

	void add_element(int data, int x, int y);

	void delete_row(int row_num) {
		rows* pointer = first_row;
		rows* prev = nullptr;
		while (pointer) {
			if (pointer->row_number == row_num) {
				if (prev) {
					prev->next_row = pointer->next_row;
				}
				else {
					first_row = pointer->next_row;
				}
				delete pointer;
				break;
			}
			prev = pointer;
			pointer = pointer->next_row;
		}

		pointer = first_row;

		while (pointer) {
			if (pointer->row_number > row_num)
				pointer->row_number--;
			pointer = pointer->next_row;
		}

		size_x--;
		return;
	}

	void delete_column(int col_num) {
		rows* pointer = first_row;
		while (pointer) {
			columns* pointer_col = pointer->column;
			while (pointer_col) {
				if (pointer_col->column_number == col_num) {
					if (!pointer_col->prev) {
						pointer->column = pointer_col->next;
						pointer_col->del();
						break;
					}
					else {
						pointer_col->del();
						break;
					}
				}
				pointer_col = pointer_col->next;
			}

			pointer_col = pointer->column;

			while (pointer_col) {
				if (pointer_col->column_number > col_num)
					pointer_col->column_number--;
				pointer_col = pointer_col->next;
			}

			pointer = pointer->next_row;
		}

		size_y--;
		return;
	}

	pair<int, int> find_max() {
		rows* pointer = first_row;
		int mx = -1e9, x = -1, y = -1;
		while (pointer) {
			columns* pointer_col = pointer->column;
			while (pointer_col) {
				if (mx<pointer_col->data) {
					mx = pointer_col->data;
					x = pointer->row_number;
					y = pointer_col->column_number;
				}
				pointer_col = pointer_col->next;
			}
			pointer = pointer->next_row;
		}
		return { x,y };
	}

	void delete_by_max() {
		pair<int, int> coordinates = find_max();

		if (coordinates.first == -1) {
			std::cout << "There is no max element!" << std::endl;
			return;
		}
		delete_column(coordinates.second);
		delete_row(coordinates.first);
	}

};

int main(int argc, const char * argv[]) {
	compressed_matrix matrix;
	matrix.read_matrix();
	cout << endl;
	matrix.print_matrix();
	matrix.delete_by_max();
	cout << endl;
	matrix.print_matrix();


	return 0;
}
