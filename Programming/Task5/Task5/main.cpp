#include <iostream>
#include <conio.h>
#include "List.h"

using namespace std;

void UI();

int main()
{
	UI();
	_getch();
	return 0;
}

void UI()
{
	char input;
	int index;
	int data;
	List newList;
	List list1;
	List list2;

	for (int i = 0; i < 40; i++) {
		newList.push_back(i);
	}


	cout << "Press '1' to add node" << endl;
	cout << "Press '2' to split comparing to N" << endl;
	cout << "Press '3' to delete the main list" << endl;
	cout << "Press '4' to print all lists" << endl;
	cout << "Press '5' to insert" << endl;
	cout << "Press '6' to delete exact node" << endl;
	cout << "Press '0' to quite" << endl;

	while (true)
	{
		cout << "Press:  ";
		cin >> input;
		switch (input) {
		case '1':
			cout << "Enter data: ";
			int newData;
			cin >> newData;
			newList.push_back(newData);
			newList.printList();
			break;
		case '2':
			cout << "Enter N: ";
			int N;
			cin >> N;
			newList.split(&newList, &list1, &list2, N);
			//newList.printList();
			list1.printList();
			list2.printList();
			break;
		case '3':
			newList.deleteList();
			newList.printList();
			break;
		case '4':
			list1.printList();
			list2.printList();
			//newList.printList();
			break;
		case '5':
			cout << "Enter index: ";
			cin >> index;
			cout << "Enter data: ";
			cin >> data;
			newList.insert(data, index);
			newList.printList();
			break;
		case '6':
			cout << "Enter index: ";
			cin >> index;
			newList.deleteExact(index);
			newList.printList();
			break;
		case '0':
			cout << "Main list: ";
			newList.deleteList();
			cout << "List1: " << endl;
			list1.deleteList();
			cout << "List2: ";
			list2.deleteList();
			return;
		}
	}

}