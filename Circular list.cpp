#include <iostream>
using namespace std;

template<class T> class Circular;

template<class T>
class ChainNode
{
	friend class Circular<T>;
public:
	ChainNode(T e) { data = e; link = 0; }
private:
	T data;
	ChainNode<T> *link;
};

template<class T>
class Circular
{
public:
	Circular() { last = 0; }

	void traversal();
	void addHead(T e);
	void addTail(T e);
	void delHead(T *e);
private:
	ChainNode<T> *last;
};

template<class T>
void Circular<T>::traversal()
{
	ChainNode<T> *pt;
	for (pt = last->link; pt != last; pt = pt->link)
	{
		cout << pt->data << " ";
	}
	cout << pt->data << endl;
}

template<class T>
void Circular<T>::addHead(T e)
{
	if (last != 0)
	{
		ChainNode<T> *newnode = new ChainNode<T>(e);
		newnode->link = last->link;
		last->link = newnode;
	}
	else
	{
		ChainNode<T> *newnode = new ChainNode<T>(e);
		last = newnode;
		last->link = last;
	}
}

template<class T>
void Circular<T>::addTail(T e)
{
	if (last != 0)
	{
		ChainNode<T> *newnode = new ChainNode<T>(e);
		newnode->link = last->link;
		last->link = newnode;
		last = newnode;
	}
	else
	{
		ChainNode<T> *newnode = new ChainNode<T>(e);
		last = newnode;
		last->link = last;
	}
}

template<class T>
void Circular<T>::delHead(T * e)
{
	ChainNode<T> *temp = last->link;
	*e = temp->data;
	last->link = temp->link;
	delete temp;
}

int main()
{
	Circular<int> a;
	Circular<char> b;
	
	for (int i = 1; i <= 100; i++)
		a.addHead(i);
	a.traversal();
	cout << endl;


	for (char i = 'a'; i <= 'z'; i++)
		b.addTail(i);
	char t;
	for (char i = 'a'; i <= 'z'; i++)
	{
		b.delHead(&t);
		cout << t << " ";
	}

	system("pause");
}
