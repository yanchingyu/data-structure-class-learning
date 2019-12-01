#include <iostream>
using namespace std;

class DblListNode
{
	friend class DblList;
public:
	DblListNode(int val);
private:
	int data;
	DblListNode *right, *left;
};


DblListNode::DblListNode(int val)
{
	data = val;
	right = left = 0;
}

class DblList
{
public:
	DblList();

	void Insert(DblListNode *p, DblListNode *x);
	void Insert_front(int e);
	void Insert_rear(int e);
	void Delete(DblListNode *x);
	void Delete_number(int num);
	void Print();
private:
	DblListNode *first;
};

DblList::DblList()
{
	first = new DblListNode(0);
	first->right = first->left = first;
}

void DblList::Insert(DblListNode * p, DblListNode * x)
{
	p->left = x;
	p->right = x->right;
	x->right->left = p;
	x->right = p;
}

void DblList::Insert_front(int e)
{
	DblListNode *newNode = new DblListNode(e);
	Insert(newNode, first);
}

void DblList::Insert_rear(int e)
{
	DblListNode *newNode = new DblListNode(e);
	DblListNode *last = new DblListNode(0);
	last = first->left;
	Insert(newNode, last);
}

void DblList::Delete(DblListNode * x)
{
	if (x == first) throw "deletion of headnode not permited";
	else
	{
		x->left->right = x->right;
		x->right->left = x->left;
	}
}

void DblList::Delete_number(int num)
{
	
	for (DblListNode *pt = first->right; pt != first; pt = pt->right)
	{
		if (pt->data == num)
		{
			Delete(pt);
		}
	}
}

void DblList::Print()
{
	cout << "	content of the doubly linked list" << endl;
	for (DblListNode *pt = first->right; pt != first; pt = pt->right)
	{
		cout << pt->data << "  ";
	}
	cout << endl;
}

int main()
{
	DblList a, b;

	cout << "Insert_front:" << endl;
	a.Insert_front(45);
	a.Insert_front(67);
	a.Insert_front(89);
	a.Insert_front(122);
	a.Insert_front(344);
	a.Print();
	a.Delete_number(89);
	a.Delete_number(122);
	a.Print();
	cout << endl;

	cout << "Insert_rear:" << endl;
	b.Insert_rear(45);
	b.Insert_rear(67);
	b.Insert_rear(89);
	b.Insert_rear(122);
	b.Insert_rear(344);
	b.Print();
	b.Delete_number(89);
	b.Delete_number(122);
	b.Print();

	system("pause");
}


