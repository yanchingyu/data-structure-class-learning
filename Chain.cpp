#include <iostream>
using namespace std;

template < class T > class Chain;		// 前向宣告

template<class T>
class ChainNode
{
	friend class Chain<T>;
public:
	ChainNode(T e) { data = e; link = 0; }
private:
	T data;
	ChainNode<T> *link;
};

template<class T>
class Chain
{
public:
	Chain() { first = 0; }		// 建構子將first初始化成0

	void add_first(T e);
	void traversal();
	void Reverse();
private:
	ChainNode<T> *first;
};

template<class T>
void Chain<T>::add_first(T e)
{
	ChainNode<T> *temp = new ChainNode<T>(e);
	temp->link = first;			//把first裡的鏈接到temp的後面
	first = temp;				//再把temp裡面的鏈覆蓋first鏈
}

template<class T>
void Chain<T>::traversal()
{
	ChainNode<T> *p1;
	for (p1 = first; p1 != NULL; p1 = p1->link)
		cout << p1->data << "  ";
	cout << endl;
}

template<class T>
void Chain<T>::Reverse()
{
	ChainNode<T> *p = first, *q = NULL;
	while (p)
	{
		ChainNode<T> *temp = q;
		q = p;
		p = p->link;
		q->link = temp;
	}
	first = q;
}

int main()
{
	Chain<const char * > a;
	Chain<int> b;

	a.add_first("apple");
	a.add_first("magic");
	a.add_first("pineapple");
	a.traversal();
	a.Reverse();
	a.traversal();

	cout << endl;
	
	b.add_first(10);
	b.add_first(20);
	b.add_first(30);
	b.add_first(40);
	b.traversal();
	b.Reverse();
	b.traversal();

	system("pause");
}


