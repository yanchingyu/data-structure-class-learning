#include <iostream>
using namespace std;

template<class T> class TwoWayList;

template<class T>
class ChainNode
{
	friend class TwoWayList<T>;
public:
	ChainNode(T val) { data = val; link = 0; };
private:
	T data;
	ChainNode<T> *link;
};

template<class T>
class TwoWayList
{
public:
	TwoWayList() { p = 0; q = 0; };

	void add_front(T e);
	void move_left();
	void move_right();
	void Print();
private:
	ChainNode<T> *p, *q, *first;
};

template<class T>
void TwoWayList<T>::add_front(T e)
{
	ChainNode<T> *tmp = new ChainNode<T>(e);
	tmp->link = p;
	p = tmp;
}

template<class T>
void TwoWayList<T>::move_left()
{
	while (p)
	{
		ChainNode<T> *tmp = q;
		q = p;
		p = p->link;
		q->link = tmp;
	}
	first = q;
}

template<class T>
void TwoWayList<T>::move_right()
{
	while (q)
	{
		ChainNode<T> *tmp = p;
		p = q;
		q = q->link;
		p->link = tmp;
	}
	first = p;
}

template<class T>
void TwoWayList<T>::Print()
{
	for (ChainNode<T> *pt = first; pt != NULL; pt = pt->link)
	{
		cout << pt->data << " ";
	}
	cout << endl;
}

int main()
{
	TwoWayList<int> list;
	list.add_front(33);
	list.add_front(44);
	list.add_front(55);

	list.move_right();
	list.Print();
	
	list.move_left();
	list.Print();

	system("pause");
}

/*
�@�A  double linked list
�G�A�����а��k  p, q two pointer			
				
						p        q

		null <-----------		 -------------> null

	list�bpq���й諸����O�V���䨫 �bpq���й�k�䪺�����O�V�k�䨫
	�Q��reverse()�̭������ʤ�k pq�i�H�ۥѥ��k����

	move left:				move right:
			r = q;					r = p;
			q = p;					p = q;
			p = p->link;			q = q->link;
			q->link = r;			p->link = r;

*/