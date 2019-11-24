#include <iostream>

using namespace std;

template <typename KeyType, typename DataType>
typename AVLTree <KeyType, DataType> ::Node* AVLTree <KeyType, DataType> ::
findRec(typename AVLTree <KeyType, DataType> ::Node *cur, KeyType key, bool exact) {
	if (cur == NULL) {
		return NULL;
	}

	if (key == cur->key) {
		return cur;
	}

	if (key < cur->key) {
		if (!exact && cur->left == NULL) {
			return cur;
		}
		return findRec(cur->left, key, exact);
	}
	if (!exact && cur->right == NULL) {
		return cur;
	}

	return findRec(cur->right, key, exact);
}

template <typename KeyType, typename DataType>
void AVLTree <KeyType, DataType> ::
leftRotate(typename AVLTree <KeyType, DataType> ::Node *cur) {
	Node *a, *b, *p, *q, *r;
	a = cur;
	b = a->right;
	p = a->left;
	q = b->left;
	r = b->right;

	if (a != root) {
		if (a->prev->left == a) {
			a->prev->left = b;
		}
		else {
			a->prev->right = b;
		}
	}
	else {
		root = b;
	}
	b->prev = a->prev;
	b->left = a;
	b->right = r;
	b->height++;
	a->left = p;
	a->right = q;
	if (q != NULL) {
		q->prev = a;
	}
	a->prev = b;
	a->height--;

	balance(a);
	balance(b);
}

template <typename KeyType, typename DataType>
void AVLTree <KeyType, DataType> ::
rightRotate(typename AVLTree <KeyType, DataType> ::Node *cur) {
	Node *a, *b, *p, *q, *r;
	a = cur;
	b = a->left;
	p = a->right;
	q = b->left;
	r = b->right;

	if (a != root) {
		if (a->prev->left == a) {
			a->prev->left = b;
		}
		else {
			a->prev->right = b;
		}
	}
	else {
		root = b;
	}
	b->prev = a->prev;
	b->right = a;
	b->left = q;
	if (r != NULL) {
		r->prev = a;
	}
	b->height++;
	a->left = r;
	a->right = p;
	a->prev = b;
	a->height--;

	balance(a);
	balance(b);
}

template <typename KeyType, typename DataType>
void AVLTree <KeyType, DataType> ::
balance(typename AVLTree <KeyType, DataType> ::Node *cur) {
	int heightLeftCur = cur->left == NULL ? 0 : cur->left->height,
		heightRightCur = cur->right == NULL ? 0 : cur->right->height;
	cur->height = max(heightLeftCur, heightRightCur) + 1;

	if (heightRightCur - heightLeftCur == 2) {
		Node *next = cur->right;
		int heightLeftNext = next->left == NULL ? 0 : next->left->height,
			heightRightNext = next->right == NULL ? 0 : next->right->height;

		if (heightLeftNext > heightRightNext) {
			// big left rotate
			rightRotate(next);
			leftRotate(cur);
		}
		else {
			// small left rotate
			leftRotate(cur);
		}
	}
	else if (heightRightCur - heightLeftCur == -2) {
		Node *next = cur->left;
		int heightLeftNext = next->left == NULL ? 0 : next->left->height,
			heightRightNext = next->right == NULL ? 0 : next->right->height;

		if (heightLeftNext < heightRightNext) {
			// big right rotate
			leftRotate(next);
			rightRotate(cur);
		}
		else {
			// // small right rotate
			rightRotate(cur);
		}
	}
}

template <typename KeyType, typename DataType>
bool AVLTree <KeyType, DataType> ::
insertRec(typename AVLTree <KeyType, DataType> ::Node *cur, KeyType key, DataType data) {
	if (key == cur->key) {
		cur->data = data;
		return false;
	}

	Node *next;
	if (key < cur->key) {
		next = cur->left;
	}
	else {
		next = cur->right;
	}

	if (next == NULL) {
		Node *newNode = new Node;
		newNode->key = key;
		newNode->data = data;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->prev = cur;
		newNode->height = 1;

		if (key < cur->key) {
			cur->left = newNode;
		}
		else {
			cur->right = newNode;
		}

		balance(cur);

		return true;
	}

	bool inserted = insertRec(next, key, data);

	if (inserted) {
		balance(cur);
	}

	return inserted;
}

template <typename KeyType, typename DataType>
bool AVLTree <KeyType, DataType> ::
eraseRec(typename AVLTree <KeyType, DataType> ::Node *cur, KeyType key) {
	if (cur == NULL) {
		return false;
	}

	if (key == cur->key) {
		if (cur->left == NULL && cur->right == NULL) {
			if (cur == root) {
				root = NULL;
			}
			else {
				if (cur->prev->left == cur) {
					cur->prev->left = NULL;
				}
				else {
					cur->prev->right = NULL;
				}
			}

			delete cur;
		}
		else if (cur->left == NULL) {
			if (cur == root) {
				root = cur->right;
			}
			else {
				if (cur->prev->left == cur) {
					cur->prev->left = cur->right;
				}
				else {
					cur->prev->right = cur->right;
				}
			}
			cur->right->prev = cur->prev;

			delete cur;
		}
		else if (cur->right == NULL) {
			if (cur == root) {
				root = cur->left;
			}
			else {
				if (cur->prev->left == cur) {
					cur->prev->left = cur->left;
				}
				else {
					cur->prev->right = cur->left;
				}
			}
			cur->left->prev = cur->prev;

			delete cur;
		}
		else {
			Node* nearest = findRec(cur->right, cur->key, false);

			cur->data = nearest->data;
			cur->key = nearest->key;

			eraseRec(cur->right, nearest->key);
		}

		balance(cur);

		return true;
	}

	bool erased;
	if (key < cur->key) {
		erased = eraseRec(cur->left, key);
	}
	else {
		erased = eraseRec(cur->right, key);
	}

	if (erased) {
		balance(cur);
	}

	return erased;
}

template <typename KeyType, typename DataType>
void AVLTree <KeyType, DataType> ::
printRec(typename AVLTree <KeyType, DataType> ::Node *cur, bool asList) {
	if (cur == NULL) {
		return;
	}

	if (asList) {
		cout << "(" << cur->key << ", " << cur->data << ")  ";
	}
	else {
		cout << cur->key << ": ";
		if (cur->left == NULL) {
			cout << "NULL" << ", ";
		}
		else {
			cout << cur->left->key << ", ";
		}
		if (cur->right == NULL) {
			cout << "NULL, ";
		}
		else {
			cout << cur->right->key << ", ";
		}
		cout << "height = " << cur->height;
		cout << ", prev = ";
		if (cur->prev == NULL) {
			cout << "NULL";
		}
		else {
			cout << cur->prev->key;
		}
		cout << endl;
	}

	printRec(cur->left, asList);
	printRec(cur->right, asList);
}

template <typename KeyType, typename DataType>
AVLTree <KeyType, DataType> ::
AVLTree() {
	root = NULL;
	size = 0;
}

template <typename KeyType, typename DataType>
AVLTree <KeyType, DataType> ::
~AVLTree() {
	while (size) {
		erase(root->key);
	}
}

template <typename KeyType, typename DataType>
bool AVLTree <KeyType, DataType> ::
insert(KeyType key, DataType data) {
	if (size == 0) {
		root = new Node;
		root->key = key;
		root->data = data;
		root->left = NULL;
		root->right = NULL;
		root->prev = NULL;
		root->height = 1;
		size = 1;

		return true;
	}
	else {
		bool inserted = insertRec(root, key, data);
		if (inserted) {
			size++;
		}

		return inserted;
	}
}

template <typename KeyType, typename DataType>
bool AVLTree <KeyType, DataType> ::
erase(KeyType key) {
	bool erased = eraseRec(root, key);
	if (erased) {
		size--;
	}

	return erased;
}

template <typename KeyType, typename DataType>
DataType* AVLTree <KeyType, DataType> ::
find(KeyType key) {
	Node* foundNode = findRec(root, key, true);
	if (foundNode == NULL) {
		return NULL;
	}
	else {
		return &(foundNode->data);
	}
}

template <typename KeyType, typename DataType>
void AVLTree <KeyType, DataType> ::
print() {
	if (size == 0) {
		cout << "AVL - tree is empty" << endl << endl;
	}
	else {
		cout << "size = " << size << endl;

		printRec(root, false);

		cout << endl;
	}
}

template <typename KeyType, typename DataType>
void AVLTree <KeyType, DataType> ::
printAsList() {
	printRec(root, true);
}

template <typename KeyType, typename DataType>
char* AVLTree <KeyType, DataType> ::
toCharPointer(string s, int n) {
	char *cptr = new char[MAX_KEY_AND_DATA_SIZE];
	cptr[0] = '(';
	for (int i = 1; i <= s.size(); i++) {
		cptr[i] = s[i - 1];
	}
	cptr[s.size() + 1] = ',';
	cptr[s.size() + 2] = ' ';
	int pos = s.size() + 3;
	if (n < 0) {
		cptr[pos++] = '-';
		n = -n;
	}
	int digits[MAX_KEY_AND_DATA_SIZE], numSize = 0;
	do {
		digits[numSize++] = n % 10;
		n /= 10;
	} while (n);
	for (int i = numSize - 1; i >= 0; i--) {
		cptr[pos++] = digits[i] + '0';
	}
	cptr[pos++] = ')';
	cptr[pos] = '\0';
	return cptr;
}

template <typename KeyType, typename DataType>
void AVLTree <KeyType, DataType> ::
fillTable(int& column, int depth, typename AVLTree <KeyType, DataType> ::Node *cur,
	typename AVLTree <KeyType, DataType> ::Node*** nodeTable) {
	if (cur == NULL) {
		return;
	}

	fillTable(column, depth + 1, cur->left, nodeTable);

	nodeTable[depth][column++] = cur;

	fillTable(column, depth + 1, cur->right, nodeTable);
}

template <typename KeyType, typename DataType>
void AVLTree <KeyType, DataType> ::
draw() {
	if (size == 0) {
		cout << "AVL - tree is empty" << endl << endl;
		return;
	}

	Node ***nodeTable = new Node**[MAX_DRAWING_SIZE];
	for (int i = 0; i < MAX_DRAWING_SIZE; i++) {
		nodeTable[i] = new Node*[MAX_DRAWING_SIZE];
	}
	for (int i = 0; i < root->height; i++) {
		for (int j = 0; j < size; j++) {
			nodeTable[i][j] = NULL;
		}
	}
	fillTable(*(new int) = 0, 0, root, nodeTable);

	int maxX = size * DRAWING_SIDE + DRAWING_SIDE / 2 + BORDER,
		maxY = root->height * DRAWING_SIDE + DRAWING_SIDE / 2 + BORDER;
	initwindow(maxX, maxY);
	setfillstyle(1, WHITE);
	bar(0, 0, maxX, maxY);

	for (int i = 0; i < root->height; i++) {
		for (int j = 0; j < size; j++) {
			Node *cur = nodeTable[i][j];

			if (cur == NULL) {
				continue;
			}

			if (i != root->height - 1) {
				if (cur->left != NULL) {
					int curJ = j - 1;
					while (nodeTable[i + 1][curJ] == NULL) {
						curJ--;
					}

					setcolor(BROWN);
					setlinestyle(0, 0, 3);
					line(j * DRAWING_SIDE + DRAWING_SIDE / 2 + BORDER,
						i * DRAWING_SIDE + DRAWING_SIDE / 2 + BORDER,
						curJ * DRAWING_SIDE + DRAWING_SIDE / 2 + BORDER,
						(i + 1) * DRAWING_SIDE + DRAWING_SIDE / 2 + BORDER);
				}
				if (cur->right != NULL) {
					int curJ = j + 1;
					while (nodeTable[i + 1][curJ] == NULL) {
						curJ++;
					}

					setcolor(BROWN);
					setlinestyle(0, 0, 3);
					line(j * DRAWING_SIDE + DRAWING_SIDE / 2 + BORDER,
						i * DRAWING_SIDE + DRAWING_SIDE / 2 + BORDER,
						curJ * DRAWING_SIDE + DRAWING_SIDE / 2 + BORDER,
						(i + 1) * DRAWING_SIDE + DRAWING_SIDE / 2 + BORDER);
				}
			}
			setcolor(GREEN);
			setfillstyle(1, GREEN);
			fillellipse(j * DRAWING_SIDE + DRAWING_SIDE / 2 + BORDER,
				i * DRAWING_SIDE + DRAWING_SIDE / 2 + BORDER,
				3 * DRAWING_SIDE / 7, 3 * DRAWING_SIDE / 7);

			setbkcolor(YELLOW);
			setcolor(BLACK);
			settextstyle(4, 0, 2);
			outtextxy(j * DRAWING_SIDE + DRAWING_SIDE / 2 - 60 + BORDER,
				i * DRAWING_SIDE + DRAWING_SIDE / 2 - 10 + BORDER,
				toCharPointer(cur->key, cur->data));
		}
	}

	getch();

	closegraph();
}
