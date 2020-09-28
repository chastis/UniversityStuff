#include <iostream>

using namespace std;

struct Data {
	int n;
	
	Data(int n) {
		this->n = n;
	}
};

struct Node {
	Data* d;
	Node* next;
	
	Node (Data* d, Node* next) {
		this->d = d;
		this->next = next;
	} 
};

class Queue {
	
	private:
		Node *h, *t;
		int size;
	
	public:
		Queue() {
			size = 0;
			h = new Node(NULL, NULL);
			t = h;
		}
		
		Data* pop() {
			if (h->next == NULL) {
				return NULL;
			}
			h = h->next;
			size--;
			return h->d;
		}
		
		Data* push(Data* d) {
			Node* newT = new Node(d, NULL);
			t->next = newT;
			t = t->next;
		}
		
		void print() {
			cout << "Queue: ";
			for (Node* it = h->next; it != NULL; it = it->next) {
				cout << it->d->n << " ";
			}
			cout << endl;
		}
};

int main() {
	Queue q;
	q.push(new Data(2));
	q.push(new Data(4));
	q.push(new Data(5));
	q.print();
	Data *d;
	if (d = q.pop()) {
		cout << "Extracted element = " << d->n << endl; 
	}
	q.print();
}
