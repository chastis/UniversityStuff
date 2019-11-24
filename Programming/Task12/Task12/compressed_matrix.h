#ifndef compressed_matrix_h
#define compressed_matrix_h

#include <stdio.h>
#include <utility>

struct columns {
	int data;
	int column_number;
	columns* next;
	columns* prev;
	columns();
	columns(int, int);
	void del();

};

struct rows {
	int row_number;
	columns* column;
	rows* next_row;
	rows();
	rows(int, columns*);
	void push_front(int, int);
	void push_back(int, int);
};

struct compressed_matrix {
	int size_x, size_y;
	rows* first_row;

	compressed_matrix();
	compressed_matrix(int, int);
	void read_matrix();
	void print_matrix();
	void push_row(int, columns*);
	void add_element(int data, int x, int y);
	void delete_row(int row_num);
	void delete_column(int col_num);

	std::pair <int, int> find_max();
	void delete_by_max();

};

#endif /* compressed_matrix_h */
