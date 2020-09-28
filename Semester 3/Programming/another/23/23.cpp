#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>

using namespace std;

const int TYPES_COUNT = 6;
const string TYPES_STR = 
	"{INTEGER - 0, SHORT - 1, CHAR - 2, STRING - 3, DOUBLE - 4, BOOL - 5}";

enum Type {
	INTEGER,
	SHORT,
	CHAR,
	STRING,
	DOUBLE,
	BOOL
};

enum Command {
	CREATE,
	ADD_ROW,
	ADD_COLUMN,
	DELETE_ROW,
	DELETE_COLUMN,
	READ,
	WRITE,
	GET,
	SET,
	PRINT,
	EXIT
};

class Converter {
	
	public:
		static int toInt(string s) {
			stringstream ss(s);
			int val;
			ss >> val;
			return val;
		}
		
		static short toShort(string s) {
			stringstream ss(s);
			bool val;
			ss >> val;
			return val;
		}	
		
		static char toChar(string s) {
			stringstream ss(s);
			char val;
			ss >> val;
			return val;
		}
		
		static double toDouble(string s) {
			stringstream ss(s);
			double val;
			ss >> val;
			return val;
		}
		
		static bool toBool(string s) {
			stringstream ss(s);
			bool val;
			ss >> val;
			return val;
		}
		
		template <typename T>
		static T toString(T val) {
			stringstream ss;
			ss << val;
			return ss.str();
		}
};

class Table {
	
	private:
		string name;
		int rowsCount, columnsCount;
		vector <string> columnsNames;
		vector <Type> types;
		vector < vector <string> > cells;
		
	public:
		Table() {
			rowsCount = columnsCount = 0;
		}
		
		Table(string name, int rowsCount, int columnsCount, 
			vector <string> columnsNames, vector <Type> types,
			vector < vector <string> > cells) : name(name), rowsCount(rowsCount),
			columnsCount(columnsCount), columnsNames(columnsNames), types(types) {
			for (auto row : cells) {
				this->cells.push_back(row);
			}
		}
		
		void addRow(vector <string> row) {
			cells.push_back(row);
			rowsCount++;
		}
		
		void addColumn(string name, Type type, vector <string> column) {
			columnsNames.push_back(name);
			types.push_back(type);
			for (int i = 0; i < rowsCount; i++) {
				cells[i].push_back(column[i]);
			}
			columnsCount++;
		}
		
		void deleteRow(int pos) {
			cells.erase(cells.begin() + pos);
			rowsCount--;
		}
		
		void deleteColumn(int pos) {
			for (int i = 0; i < rowsCount; i++) {
				cells[i].erase(cells[i].begin() + pos);
			}
			columnsNames.erase(columnsNames.begin() + pos);
			types.erase(types.begin() + pos);
			columnsCount--;
		}
		
		static Table readFromFile(string fileName) {
			ifstream fin(fileName);
			string name;
			int rowsCount, columnsCount;
			vector <string> columnsNames;
			vector <Type> types;
			getline(fin, name);
			fin >> rowsCount;
			fin >> columnsCount;
			fin.ignore();
			for (int i = 0; i < columnsCount; i++) {
				string name;
				getline(fin, name);
				columnsNames.push_back(name);
			}
			for (int i = 0; i < columnsCount; i++) {
				int type;
				fin >> type;
				types.push_back((Type)type);
			}	
			vector < vector <string> > cells(rowsCount);
			for (int i = 0; i < rowsCount; i++) {
				cells[i].resize(columnsCount);
			}
			fin.ignore();
			for (int i = 0; i < rowsCount; i++) {
				for (int j = 0; j < columnsCount; j++) {
					getline(fin, cells[i][j]);
				}
			}
			Table table(name, rowsCount, columnsCount, columnsNames, types, cells);
			return table;
		}
		
		void writeToFile(string fileName) {
			ofstream fout(fileName);
			fout << name << endl;
			fout << rowsCount << endl;
			fout << columnsCount << endl;
			for (auto columnName : columnsNames) {
				fout << columnName << endl;
			}
			for (auto type : types) {
				fout << (int)type << endl; 
			}
			for (auto row : cells) {
				for (auto val : row) {
					fout << val << endl;
				}
			}
		}
		
		string getValue(int i, int j) {
			return cells[i][j];
		}
		
		void setValue(int i, int j, string val) {
			cells[i][j] = val;
		}
		
		int getRowsCount() {
			return rowsCount;
		}
		
		int getColumnsCount() {
			return columnsCount;
		}
		
		Type getType(int column) {
			return types[column];
		}
		
		void print() {
			cout << endl;
			cout << "-------------------------------------" << endl;
			cout << "Table: " << name << endl;
			cout << "-------------------------------------" << endl;
			for (int i = 0; i < columnsCount; i++) {
				cout << columnsNames[i] << "(";
				string type = "";
				switch (types[i]) {
					case INTEGER : type = "int"; break;
					case SHORT : type = "short"; break;
					case CHAR : type = "char"; break;
					case STRING : type = "string"; break;
					case DOUBLE : type = "double"; break;
					case BOOL : type = "bool"; break;
				}
				cout << type << ")  ";
			}
			cout << endl;
			for (auto row : cells) {
				for (int i = 0; i < row.size(); i++) {
					if (types[i] == BOOL) {
						cout << (row[i] == "0" ? "false  " : "true  ");
					} else {
						cout << row[i] << "  ";
					}
				}
				cout << endl;
			}
			cout << endl;
		}
};

Table table;

void showMenu() {
	cout << endl;
	cout << "-------------------------------------" << endl;
	cout << "               MENU                  " << endl;
	cout << "-------------------------------------" << endl;
	cout << "Create table - 0" << endl;
	cout << "Add row - 1" << endl;
	cout << "Add column - 2" << endl;
	cout << "Delete row - 3" << endl;
	cout << "Delete column - 4" << endl;
	cout << "Read table from file - 5" << endl;
	cout << "Write table to file - 6" << endl;
	cout << "Get element - 7" << endl;
	cout << "Set element - 8" << endl;
	cout << "Print table - 9" << endl;
	cout << "Exit - e" << endl; 
	cout << "-------------------------------------" << endl << endl;
}

void createTable() {
	string name;
	int rowsCount, columnsCount;
	vector <string> columnsNames;
	vector <Type> types;
	cout << "Table name: ";
	getline(cin, name);
	cout << "Number of rows = "; 
	cin >> rowsCount;
	cout << "Number of columns = ";
	cin >> columnsCount;
	cin.ignore();
	cout << "Enter columns names:" << endl;
	for (int i = 0; i < columnsCount; i++) {
		string name;
		getline(cin, name);
		columnsNames.push_back(name);
	}
	cout << "Enter columns types from set " << TYPES_STR << endl;
	for (int i = 0; i < columnsCount; i++) {
		int type;
		cin >> type;
		types.push_back((Type)type);
	}	
	vector < vector <string> > cells(rowsCount);
	for (int i = 0; i < rowsCount; i++) {
		cells[i].resize(columnsCount);
	}
	cin.ignore();
	cout << "Enter elements (left->right, top->down): " << endl;
	for (int i = 0; i < rowsCount; i++) {
		for (int j = 0; j < columnsCount; j++) {
			getline(cin, cells[i][j]);
		}
		cout << endl;
	}
	Table table(name, rowsCount, columnsCount, columnsNames, types, cells);
	::table = table;
}

void addRow() {
	vector <string> row(table.getColumnsCount());
	for (int i = 0; i < table.getColumnsCount(); i++) {
		cout << "Next value = ";
		cin >> row[i];
	}
	table.addRow(row);
}

void addColumn() {
	string name;
	cout << "Columns name: ";
	cin >> name;
	cout << "Enter column type from set " << TYPES_STR << endl;
	int typeInt;
	cin >> typeInt;
	Type type = (Type)typeInt;
	vector <string> column(table.getRowsCount());
	for (int i = 0; i < table.getRowsCount(); i++) {
		cout << "Next value = ";
		cin >> column[i];
	}
	table.addColumn(name, type, column);
}

void deleteRow() {
	cout << "Position of deleting row = ";
	int pos;
	cin >> pos;
	table.deleteRow(pos);
}

void deleteColumn() {
	cout << "Position of deleting column = ";
	int pos;
	cin >> pos;
	table.deleteColumn(pos);
}

void readTable() {
	cout << "File name (*.txt) = ";
	string fileName;
	cin >> fileName;
	table = Table::readFromFile(fileName);
}

void writeTable() {
	cout << "File name (*.txt) = ";
	string fileName;
	cin >> fileName;
	table.writeToFile(fileName);
}

void getValue() {
	int i, j;
	cout << "row = ";
	cin >> i;
	cout << "column = ";
	cin >> j;
	cout << "T[" << i << "][" << j << "] = " <<
		table.getValue(i, j) << endl;
}

void setValue() {
	int i, j;
	cout << "row = ";
	cin >> i;
	cout << "column = ";
	cin >> j;
	string val;
	cout << "value = ";
	cin >> val;
	table.setValue(i, j, val);
}

void print() {
	table.print();
}

int main() {
	while (true) {
		showMenu();
		char opCh = getch();
		int op = (opCh == 'e' ? 10 : opCh - '0');
		switch (op) {
			case CREATE : createTable(); break;
			case ADD_ROW : addRow(); break;
			case ADD_COLUMN : addColumn(); break;
			case DELETE_ROW : deleteRow(); break;
			case DELETE_COLUMN : deleteColumn(); break;
			case READ : readTable(); break;
			case WRITE : writeTable(); break;
			case GET : getValue(); break;
			case SET : setValue(); break;
			case PRINT : print(); break;
			case EXIT : return 0; 
		}
	}
}

