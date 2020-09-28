#include <iostream>
#include <string>

#define SIZE_CASUAL 3
#define SIZE_VIP 2
#define UINT unsigned int

class Shop;

enum class list_status
{
	casual,
	VIP
};

template <class T>
struct Node
{
	T data;
	Node * next;
};

template <class T>
class Queue
{
public:
	Queue()
	{
		head = 0;
		tail = 0;
		size = 0;
	}
	~Queue()
	{

	}
	UINT size()
	{
		return _size;
	}
	void push_back(T const &a)
	{
		_size++;
		if (head)
		{
			Node<T> * temp = new Node<T>;
			temp->data = a;
			tail = temp;
		}
		else
		{
			Node<T> * temp = new Node<T>;
			temp->data = a;
			head = temp;
			tail = temp;
		}
	}
	void push_front(T const &a)
	{
		_size++;
		if (head)
		{
			Node<T> * temp = new Node<T>;
			temp->data = a;
			temp->next = head;
			head = temp;
		}
		else
		{
			Node<T> * temp = new Node<T>;
			temp->data = a;
			head = temp;
			tail = temp;
		}
	}
	void delete_first()
	{
		if (head)
		{
			Node<T> * temp = head->next;
			delete head;
			head = temp;
			size--;
		}
	}
	T * get_data(UINT const &i = 0)
	{
		if (i >= _size) return NULL;
		UINT j = i;
		Node<T> * temp = head;
		if (head)
		{
			while (j != 0)
			{
				temp = head->next;
				j--;
			}
			return &temp->data;
		}
		return NULL;
	}
private:
	Node<T> * head;
	Node<T> * tail;
	UINT _size;
};

class Item
{
public:
	friend class Customer;
	friend class Shop;
	Item()
	{
		price = 0;
		name = "";
		count = 0;
	}
	~Item() {};
	UINT price;
	std::string name;
	UINT count;
private:

};

class Customer
{
public:
	friend class Shop;
	Customer()
	{
		money = 0;
	}
	~Customer() {};
	void add_product(Item const &product)
	{
		products.push_front(product);
	}
private:
	UINT money;
	list_status status;
	Queue<Item> products;

};

class Shop
{
public:
	Shop()
	{
		vip_count = 0;
		casual_count = 0;
	};
	~Shop() {};
	void add_person(Customer const &person)
	{
		if (person.status == list_status::VIP && vip_count < SIZE_VIP)
		{
			people.push_front(person);
			vip_count++;
		}
		else if (person.status == list_status::casual && vip_count < SIZE_CASUAL)
		{
			people.push_front(person);
			casual_count++;
		}
	}
	void add_good(Item const &good)
	{
		goods.push_back(good);
	}
	void work()
	{
		while (people.size() != 0)
		{
			Customer * temp_customer = people.get_data();
			bool flag = true;
			while (flag)
			{
				Item * temp_item = temp_customer->products.get_data();
				UINT i = 0;
				for (; i < goods.size(); i++)
				{
					if (temp_item->name == goods.get_data(i)->name) break;
				}
				if (i == goods.size() || goods.get_data(i)->count == 0 || goods.get_data(i)->price > temp_customer->money)
				{
					temp_customer->products.delete_first();
					if (temp_customer->products.size() == 0) flag = false;

				}
				else
				{
					goods.get_data(i)->count--;
					temp_item->count--;
					temp_customer->money -= goods.get_data(i)->price;
					if (temp_item->count == 0) temp_customer->products.delete_first();
					if (temp_customer->products.size() == 0) flag = false;
				}
				
			}
		}
	}
private:
	Queue<Item> goods;
	Queue<Customer> people;
	UINT vip_count;
	UINT casual_count;
};

int main()
{

	return 0;
}
