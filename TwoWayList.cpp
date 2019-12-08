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

	void move_right();  // 移動到右邊一個位置
	void move_left();  // 移動到左邊一個位置 
	void move_first();  // 移動到最開頭
	void move_last();   // 移動到最末端	
	void left_to_right_traversal();  // 由左到右走訪所有node 
	void right_to_left_traversal();  // 由右到左走訪所有node 
	void insert_front(T val);   // 插入數值到最前面的位置 
	void insert_rear(T val);  // 插入數值到最後面的位置 
private:
	ChainNode<T> *p, *q;
};

/*...指標q裡只會有一個數字，剩下數字在指標p裡*/
template<class T>
void TwoWayList<T>::move_right()
{
	ChainNode<T> *r = p;
	p = q;
	q = q->link;
	p->link = r;
}

/*...指標p裡只會有一個數字，剩下數字在指標q裡*/
template<class T>
void TwoWayList<T>::move_left()
{
	ChainNode<T> *r = q;
	q = p;
	p = p->link;
	q->link = r;
}

//  p裡只能有一個數字，因此當有數字加到p才會執行
template<class T>
void TwoWayList<T>::move_first()
{
	while (p->link != 0)
	{
		move_left();
	}
}

//  q裡只能有一個數字，因此當有數字加到q才會執行
template<class T>
void TwoWayList<T>::move_last()
{
	while (q->link != 0)
	{
		move_right();
	}
}

/*...由p來輸出，會將q裡的數字一個一個提到p的開頭，在輸出p的開頭*/
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

/*...由q來輸出，會將p裡的數字一個一個提到q的開頭，在輸出q的開頭*/
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

	cout << "左邊到右邊走訪:\n\t";
	list.left_to_right_traversal();
	cout << "右邊到左邊走訪:\n\t";
	list.right_to_left_traversal();

	system("pause");
}

/*
一，  double linked list
二，雙指標做法  p, q two pointer

						p        q

		null <-----------		 -------------> null

	list在pq指標對的左邊是向左邊走 在pq指標對右邊的部分是向右邊走
	利用reverse()裡面的移動方法 pq可以自由左右移動

	move left:				move right:
			r = q;					r = p;
			q = p;					p = q;
			p = p->link;			q = q->link;
			q->link = r;			p->link = r;

*/
