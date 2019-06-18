#ifndef TREE_2_3_4_H
#define TREE_2_3_4_H


class Node
{
public:
	Node()
	{
		amount_data = 1;
		left = 0;
		right = 0;
		prev = 0;
	}
	int amount_data;
	Node * left;
	Node * right;
	Node * prev;
	void change_child(Node * new_child)
	{
		Node * temp = prev;
		if (temp->left == this)
		{
			temp->left = new_child;
			return;
		}
		if (temp->right == this)
		{
			temp->right = new_child;
			return;
		}
		if (temp->amount_data == 2)
		{
			if (((Three_Node *)temp)->middle == this)
				((Three_Node *)temp)->middle = new_child;
			return;
		}
		if (temp->amount_data == 3)
		{
			if (((Four_Node *)temp)->middle_left == this)
				((Four_Node *)temp)->middle_left = new_child;
			if (((Four_Node *)temp)->middle_right == this)
				((Four_Node *)temp)->middle_right = new_child;
			return;
		}
	}
	void update(int a, Node * one, Node * two)
	{
		switch (amount_data)
		{
		case 1:
		{
			Three_Node * new_n = new Three_Node;
			new_n->prev = prev;
			if (a < ((Two_Node *)this)->data[0])
			{
				new_n->middle = one;
				new_n->right = two;
				new_n->left = this->left;
				new_n->data[1] = a;
				new_n->data[0] = ((Two_Node *)this)->data[0];
			} 
			else if (a > ((Two_Node *)this)->data[0])
			{
				new_n->left = one;
				new_n->middle = two;
				new_n->right = this->right;
				new_n->data[0] = a;
				new_n->data[1] = ((Two_Node *)this)->data[0];
			}
		}
		case 2:
		{
			Four_Node * new_n = new Four_Node;
			new_n->prev = prev;
			if (((Three_Node *)this)->data[0] > a)
			{
				new_n->middle = one;
				new_n->right = two;
				new_n->left = this->left;
				new_n->data[1] = a;
				new_n->data[0] = ((Two_Node *)this)->data[0];
			}
			else if (((Three_Node *)temp)->data[0] < a && a < ((Three_Node *)temp)->data[1])
			{
				if (((Three_Node *)temp)->middle != 0)
				{
					temp = ((Three_Node *)temp)->middle;
					break;
				}
				else
				{
					//insert
					Four_Node * new_node = new Four_Node;
					new_node->data[1] = a;
					new_node->data[0] = ((Three_Node *)temp)->data[0];
					new_node->data[2] = ((Three_Node *)temp)->data[1];
					temp->change_child(new_node);
					delete temp;
				}
			}
			else if (((Three_Node *)temp)->data[1] < a)
			{
				if (((Three_Node *)temp)->right != 0)
				{
					temp = temp->right;
					break;
				}
				else
				{
					//insert
					Four_Node * new_node = new Four_Node;
					new_node->data[2] = a;
					new_node->data[0] = ((Three_Node *)temp)->data[0];
					new_node->data[1] = ((Three_Node *)temp)->data[1];
					temp->change_child(new_node);
					delete temp;
				}
			}
			//we already have this element
			else return;

		}
		case 3:
		{

		}
		default:
			break;
		}
	}
};

class Two_Node : public Node
{
public:
	int data[1];
};

class Three_Node : public Node
{
public:
	Three_Node() : Node()
	{
		amount_data = 2;
		middle = 0;
	}
	int data[2];
	Node * middle;
};

class Four_Node : public Node
{
public:
	Four_Node() : Node()
	{
		amount_data = 3;
		middle_left = 0;
		middle_right = 0;
	}
	void split(int a)
	{
		Two_Node * one = new Two_Node;
		Three_Node * two = new Three_Node;
		one->prev = this;
		two->prev = this;
		if (a < data[0])
		{
			one->data[0] = a;
			a = data[0];
			two->data[0] = data[1];
			two->data[1] = data[2];
		}
		else if (a > data[0] && a < data[1])
		{
			one->data[0] = data[0];
			//a=a
			two->data[0] = data[1];
			two->data[1] = data[2];
		}
		else if (a > data[1] && a < data[2])
		{
			one->data[0] = data[0];
			two->data[0] = a;
			a = data[1];
			two->data[1] = data[2];
		} else if (a > data[2])
		{
			one->data[0] = data[0];
			two->data[0] = data[2];
			two->data[1] = a;
			a = data[1];
		}
		else return;
		prev->update(a, one, two);
		delete this;
	}
	int data[3];
	Node * middle_left;
	Node * middle_right;
};

class Tree_2_3_4
{
public:
	Tree_2_3_4()
	{
		head = 0;
	}
	~Tree_2_3_4()
	{
	}
	void insert(int a)
	{
		if (head == 0)
		{
			Two_Node * temp = new Two_Node;
			temp->data[0] = a;
			head = temp;
		}
		else
		{
			Node * temp = head;
			while (1)
			{
				switch (temp->amount_data)
				{
				//twonode
				case 1:
				{
					//todo
					//https://habr.com/ru/post/273687/
					//
					if (((Two_Node *)temp)->data[0] > a)
					{
						if (((Two_Node *)temp)->left != 0)
						{
							temp = temp->left;
							break;
						}
						else
						{
							//insert
							Three_Node * new_node = new Three_Node;
							new_node->data[0] = a;
							new_node->data[1] = ((Two_Node *)temp)->data[0];
							temp->change_child(new_node);
							delete temp;
							
						}
					}
					else if (((Two_Node *)temp)->data[0] < a)
					{
						if (((Two_Node *)temp)->right != 0)
						{
							temp = temp->right;
							break;
						}
						else
						{
							//insert
							Three_Node * new_node = new Three_Node;
							new_node->data[1] = a;
							new_node->data[0] = ((Two_Node *)temp)->data[0];
							temp->change_child(new_node);
							delete temp;
						}
					}
					//we already have this element
					else return;
					break;
				}
				//threenode
				case 2:
				{
					if (((Three_Node *)temp)->data[0] > a)
					{
						if (((Three_Node *)temp)->left != 0)
						{
							temp = temp->left;
							break;
						}
						else
						{
							//insert
							Four_Node * new_node = new Four_Node;
							new_node->data[0] = a;
							new_node->data[1] = ((Three_Node *)temp)->data[0];
							new_node->data[2] = ((Three_Node *)temp)->data[1];
							temp->change_child(new_node);
							delete temp;

						}
					}
					else if (((Three_Node *)temp)->data[0] < a && a < ((Three_Node *)temp)->data[1])
					{
						if (((Three_Node *)temp)->middle != 0)
						{
							temp = ((Three_Node *)temp)->middle;
							break;
						}
						else
						{
							//insert
							Four_Node * new_node = new Four_Node;
							new_node->data[1] = a;
							new_node->data[0] = ((Three_Node *)temp)->data[0];
							new_node->data[2] = ((Three_Node *)temp)->data[1];
							temp->change_child(new_node);
							delete temp;
						}
					}
					else if (((Three_Node *)temp)->data[1] < a)
					{
						if (((Three_Node *)temp)->right != 0)
						{
							temp = temp->right;
							break;
						}
						else
						{
							//insert
							Four_Node * new_node = new Four_Node;
							new_node->data[2] = a;
							new_node->data[0] = ((Three_Node *)temp)->data[0];
							new_node->data[1] = ((Three_Node *)temp)->data[1];
							temp->change_child(new_node);
							delete temp;
						}
					}
					//we already have this element
					else return;
					break;
				}
				//fournode
				case 3:
				{
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////************************/todo

					if (((Four_Node *)temp)->data[0] > a)
					{
						if (((Four_Node *)temp)->left != 0)
						{
							temp = temp->left;
							break;
						}
						else
						{
							//insert
							//split


						}
					}
					else if (((Four_Node *)temp)->data[0] < a && a < ((Four_Node *)temp)->data[1])
					{
						if (((Four_Node *)temp)->middle_left != 0)
						{
							temp = ((Four_Node *)temp)->middle_left;
							break;
						}
						else
						{
							//insert
							
						}
					}
					else if (((Four_Node *)temp)->data[1] < a && a < ((Four_Node *)temp)->data[2])
					{
						if (((Four_Node *)temp)->middle_right != 0)
						{
							temp = ((Four_Node *)temp)->middle_right;
							break;
						}
						else
						{
							//insert
							
						}
					}
					else if (((Four_Node *)temp)->data[2] < a)
					{
						if (((Four_Node *)temp)->right != 0)
						{
							temp = temp->right;
							break;
						}
						else
						{
							//insert
							
						}
					}
					//we already have this element
					else return;
					break;
				}
				}
			}
		}
	}
private:
	Node * head;

};



#endif // !2_3_4_TREE_H