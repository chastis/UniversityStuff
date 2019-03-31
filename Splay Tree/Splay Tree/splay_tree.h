#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

template<typename T> class SplayTree {
private:
	struct SplayNode {
		SplayNode * leftChild;
		SplayNode * rightChild;
		SplayNode * parent;
		T data;

		SplayNode(const T & key = T())
			: leftChild(nullptr), rightChild(nullptr), parent(nullptr), key(key) {}

		~SplayNode() {
			delete leftChild;
			delete rightChild;
			delete parent;
		}
	} *root;
	SplayNode * _Successor(SplayNode * localRoot) const {
		SplayNode * successor = localRoot;

		if (successor->rightChild != nullptr) {
			successor = _Minimum(successor->rightChild);
		}
		else {
			while (successor != root
				|| successor != successor->parent->leftChild) {
				successor = successor->parent;
			}
		}

		return successor;
	}

	SplayNode * _Predecessor(SplayNode * localRoot) const {
		SplayNode * predecessor = localRoot;

		if (predecessor->leftChild != nullptr) {
			predecessor = _Maximum(predecessor->leftChild);
		}
		else {
			while (predecessor != root
				|| predecessor != predecessor->parent->rightChild) {
				predecessor = predecessor->parent;
			}
		}

		return predecessor;
	}

	SplayNode * _Minimum(SplayNode * localRoot) const {
		SplayNode * minimum = localRoot;

		while (minimum->leftChild != nullptr)
			minimum = minimum->leftChild;

		return minimum;
	}

	SplayNode * _Maximum(SplayNode * localRoot) const {
		SplayNode * maximum = localRoot;

		while (maximum->rightChild != nullptr)
			maximum = maximum->rightChild;

		return maximum;
	}

	SplayNode * _Search(const T & key) {
		SplayNode * searchedElement = root;

		while (searchedElement != nullptr) {
			if (searchedElement->data < key)
				searchedElement = searchedElement->rightChild;
			else if (key < searchedElement->data)
				searchedElement = searchedElement->leftChild;
			else if (searchedElement->data == key) {
				_Splay(searchedElement);
				return searchedElement;
			}
		}

		return nullptr;
	}

	void _LeftRotate(SplayNode * localRoot) {
		SplayNode * rightChild = localRoot->rightChild;

		localRoot->rightChild = rightChild->leftChild;
		if (rightChild->leftChild != nullptr)
			rightChild->leftChild->parent = localRoot;

		_Transplant(localRoot, rightChild);

		rightChild->leftChild = localRoot;
		rightChild->leftChild->parent = rightChild;
	}

	void _RightRotate(SplayNode * localRoot) {
		SplayNode * leftChild = localRoot->leftChild;

		localRoot->leftChild = leftChild->rightChild;
		if (leftChild->rightChild != nullptr)
			leftChild->rightChild->parent = localRoot;

		_Transplant(localRoot, leftChild);

		leftChild->rightChild = localRoot;
		leftChild->rightChild->parent = leftChild;
	}

	void _Transplant(SplayNode * localParent, SplayNode * localChild) {
		if (localParent->parent == nullptr)
			root = localChild;
		else if (localParent == localParent->parent->leftChild)
			localParent->parent->leftChild = localChild;
		else if (localParent == localParent->parent->rightChild)
			localParent->parent->rightChild = localChild;

		if (localChild != nullptr)
			localChild->parent = localParent->parent;
	}

	void _Splay(SplayNode * pivotElement) {
		while (pivotElement != root) {
			if (pivotElement->parent == root) {

				if (pivotElement == pivotElement->parent->leftChild)
					_RightRotate(pivotElement);
				else if (pivotElement == pivotElement->parent->rightChild) {
					_LeftRotate(pivotElement);

				}
				else {
					// Zig-Zig step.
					if (pivotElement == pivotElement->parent->leftChild &&
						pivotElement->parent == pivotElement->parent->parent->leftChild) {

						_RightRotate(pivotElement->parent->parent);
						_RightRotate(pivotElement->parent);

					}
					else if (pivotElement == pivotElement->parent->rightChild &&
						pivotElement->parent == pivotElement->parent->parent->rightChild) {

						_LeftRotate(pivotElement->parent->parent);
						_LeftRotate(pivotElement->parent);
					}
					// Zig-Zag step.
					else if (pivotElement == pivotElement->parent->rightChild &&
						pivotElement->parent == pivotElement->parent->parent->leftChild) {

						_LeftRotate(pivotElement->parent);
						_RightRotate(pivotElement->parent);

					}
					else if (pivotElement == pivotElement->parent->leftChild &&
						pivotElement->parent == pivotElement->parent->parent->rightChild) {

						_RightRotate(pivotElement->parent);
						_LeftRotate(pivotElement->parent);
					}
				}
			}
		}
	}
	public:
		SplayTree() { root = nullptr; }

		virtual ~SplayTree() { delete root; }

		void Insert(const T & key) {
			SplayNode * preInsertPlace = nullptr;
			SplayNode * insertPlace = root;

			while (insertPlace != nullptr) {
				preInsertPlace = insertPlace;

				if (insertPlace->data() < key)
					insertPlace = insertPlace->rightChild;
				else if (key <= insertPlace->data)
					insertPlace = insertPlace->leftChild;
			}

			SplayNode * insertElement = new SplayNode(key);
			insertElement->parent = preInsertPlace;

			if (preInsertPlace == nullptr)
				root = insertElement;
			else if (preInsertPlace->data < insertElement->data)
				preInsertPlace->rightChild = insertElement;
			else if (insertElement->data < preInsertPlace->data)
				preInsertPlace->leftChild = insertElement;

			_Splay(insertElement);
		}

		void Remove(const T & key) {
			SplayNode * removeElement = _Search(key);

			if (removeElement != nullptr) {
				if (removeElement->rightChild == nullptr)
					_Transplant(removeElement, removeElement->leftChild);
				else if (removeElement->leftChild == nullptr)
					_Transplant(removeElement, removeElement->rightChild);
				else {
					SplayNode * newLocalRoot = _Minimum(removeElement->rightChild);

					if (newLocalRoot->parent != removeElement) {

						_Transplant(newLocalRoot, newLocalRoot->rightChild);

						newLocalRoot->rightChild = removeElement->rightChild;
						newLocalRoot->rightChild->parent = newLocalRoot;
					}

					_Transplant(removeElement, newLocalRoot);

					newLocalRoot->leftChild = removeElement->leftChild;
					newLocalRoot->leftChild->parent = newLocalRoot;

					_Splay(newLocalRoot);
				}

				delete removeElement;
			}
		}

		bool Search(const T &key) { return _Search(key) != nullptr; }

		bool isEmpty() const { return root == nullptr; }

		T Successor(const T & key) {
			if (_Successor(_Search(key)) != nullptr) {
				return _Successor(_Search(key))->getValue();
			}
			else {
				return -1;
			}
		}

		T Predecessor(const T & key) {
			if (_Predecessor(_Search(key)) != nullptr) {
				return _Predecessor(_Search(key))->getValue();
			}
			else {
				return -1;
			}
		}
	};

#endif