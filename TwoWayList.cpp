#include <iostream>
using namespace std;

template<class T> class Chain;
template<class T> class TwoWayList;

template<class T>
class ChainNode
{
	friend class Chain<T>;
	friend class TwoWayList<T>;
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
	Chain() { first = 0; }
private:
	ChainNode<T> *first;
};

template<class T>
class TwoWayList
{
public:
	TwoWayList() { p = 0; q = 0; }

	void move_right();  // ���ʨ�k��@�Ӧ�m
	void move_left();  // ���ʨ쥪��@�Ӧ�m 
	void move_first();  // ���ʨ�̶}�Y
	void move_last();   // ���ʨ�̥���	
	void left_to_right_traversal();  // �ѥ���k���X�Ҧ�node 
	void right_to_left_traversal();  // �ѥk�쥪���X�Ҧ�node 
	void insert_front(T val);   // ���J�ƭȨ�̫e������m 
	void insert_rear(T val);  // ���J�ƭȨ�̫᭱����m 
private:
	ChainNode<T> *p, *q;
};

/*...����q�̥u�|���@�ӼƦr�A�ѤU�Ʀr�b����p��*/
template<class T>
void TwoWayList<T>::move_right()
{
	ChainNode<T> *r = p;
	p = q;
	q = q->link;
	p->link = r;
}

/*...����p�̥u�|���@�ӼƦr�A�ѤU�Ʀr�b����q��*/
template<class T>
void TwoWayList<T>::move_left()
{
	ChainNode<T> *r = q;
	q = p;
	p = p->link;
	q->link = r;
}

//  p�̥u�঳�@�ӼƦr�A�]�����Ʀr�[��p�~�|����
template<class T>
void TwoWayList<T>::move_first()
{
	while (p->link != 0)
	{
		move_left();
	}
}

//  q�̥u�঳�@�ӼƦr�A�]�����Ʀr�[��q�~�|����
template<class T>
void TwoWayList<T>::move_last()
{
	while (q->link != 0)
	{
		move_right();
	}
}

/*...��p�ӿ�X�A�|�Nq�̪��Ʀr�@�Ӥ@�Ӵ���p���}�Y�A�b��Xp���}�Y*/
template<class T>
void TwoWayList<T>::left_to_right_traversal()
{
	move_first();
	cout << p->data << " ";
	while (q->link != 0)
	{
		move_right();
		cout << p->data << " ";
	}
	cout << q->data << endl;
}

/*...��q�ӿ�X�A�|�Np�̪��Ʀr�@�Ӥ@�Ӵ���q���}�Y�A�b��Xq���}�Y*/
template<class T>
void TwoWayList<T>::right_to_left_traversal()
{
	move_last();
	cout << q->data << " ";
	while (p->link != 0)
	{
		move_left();
		cout << q->data << " ";
	}
	cout << p->data << endl;
}

template<class T>
void TwoWayList<T>::insert_front(T val)
{
	ChainNode<T> *temp = new ChainNode<T>(val);
	if (p)
	{
		move_first();
		p->link = temp;
	}
	else
	{
		p = temp;
	}
}

template<class T>
void TwoWayList<T>::insert_rear(T val)
{
	ChainNode<T> *temp = new ChainNode<T>(val);
	if (q)
	{
		move_last();
		q->link = temp;
	}
	else
	{
		q = temp;
	}
}

int main()
{
	TwoWayList<int> list;

	list.insert_front(44);
	list.insert_front(55);
	list.insert_front(66);
	list.insert_front(77);
	list.insert_rear(88);

	cout << "�����k�䨫�X:\n\t";
	list.left_to_right_traversal();
	cout << "�k��쥪�䨫�X:\n\t";
	list.right_to_left_traversal();

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
