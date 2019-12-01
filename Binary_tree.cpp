#include <iostream>
using namespace std;

/*...........................class Queue.............................*/

template<class T>
class Queue {
public:
	Queue(int cap);
	void Add(T e);
	T Del();

	bool isEmpty();
private:
	int front, rear;
	T *array;
	int capacity;
};

template<class T>
Queue<T>::Queue(int cap):capacity(cap)
{
	array = new T[capacity];
	front = rear = 0;
}

template<class T>
void Queue<T>::Add(T e)
{
	if (++rear % capacity == front) throw "queue is full";
	else
	{
		array[rear] = e;
	}
}

template<class T>
T Queue<T>::Del()
{
	if (front == rear) throw "queue is empty";
	else
	{
		front = ++front % capacity;
		return array[front];
	}
}

template<class T>
bool Queue<T>::isEmpty()
{
	if (front == rear) return true;
	else return false;
}


/*...........................class TreeNode.............................*/
template<class T> class Tree;

template<class T>
class TreeNode
{
	friend class Tree<T>;
public:
	TreeNode(T e);
private:
	T data;
	TreeNode<T> *leftChild, *rightChild;
};

template<class T>
TreeNode<T>::TreeNode(T e)
{
	data = e;
	leftChild = rightChild = 0;
}

/*...........................class Tree.............................*/
template<class T>
class Tree
{
public:
	Tree() { root = 0; }

	void Insert(T e);
	void Plot();
	void LevelOrder();

	void buildTree();
private:
	TreeNode<T> *root;
};

template<class T>
void Tree<T>::Insert(T e)				
{
	TreeNode<T> *tmp = new TreeNode<T>(e), *pt;
	
	if (!root)
		root = tmp;
	else
	{
		pt = root;
		while (1)
		{
			if (tmp->data <= pt->data)		/*�u�ntmp�p�G��pt�p�N�����A�S��k�����N����*/
			{
				if (!pt->leftChild)
				{
					pt->leftChild = tmp;
					break;
				}
				pt = pt->leftChild;
			}
			else							/*�u�ntmp�p�G��pt�j�N���k�A�S��k���k�N����*/
			{
				if (!pt->rightChild)
				{
					pt->rightChild = tmp;
					break;
				}
				pt = pt->rightChild;
			}
		}
	}
}

struct tmpT
{
	TreeNode<char> *nd;
	int v1, v2;
};

#define MAX_LEVEL 6
#define RESOLUTION 2
#define LEFT_MARGINE 1
template<class T>
void Tree<T>::Plot()
{
	TreeNode<T> *pt;
	Queue<tmpT> q(100);
	tmpT ele;
	int ord, lev, now_pos, sps, now_lev;
	int idx;
	double s, b;

	ele.nd = root;
	ele.v1 = 1;
	ele.v2 = 1;
	q.Add(ele);
	cout << endl;
	now_lev = 1; now_pos = 0;
	while (!q.isEmpty())
	{
		ele = q.Del();
		pt = ele.nd; ord = ele.v1; lev = ele.v2;
		if (pt->leftChild) {
			ele.nd = pt->leftChild; ele.v1 = ord * 2 - 1; ele.v2 = lev + 1;
			q.Add(ele);
		}
		if (pt->rightChild) {
			ele.nd = pt->rightChild; ele.v1 = ord * 2; ele.v2 = lev + 1;
			q.Add(ele);
		}
		// * get idx, which counts from MAX_LEVEL (=1)
		idx = MAX_LEVEL - lev + 1;
		// * adjust position (now_pos)
		if (lev > now_lev) {
			cout << endl << endl;
			now_pos = 0;
			now_lev = lev;
		}
		// * calculate spaces (sps)
		s = pow(2.0, (double)(idx - 1));
		b = s / 2 - 0.5;
		sps = b + s * (ord - 1);
		sps *= RESOLUTION;
		sps += LEFT_MARGINE;
		// * print out sps
		while (now_pos < sps) {
			cout << " "; now_pos++;
		}
		// * print the data
		cout << pt->data; now_pos++;
	}
}

template<class T>
void Tree<T>::LevelOrder()
{
	Queue<TreeNode<T>*> queue(20);
	TreeNode<T> *tree = root;

	cout << tree->data;
	while (tree)
	{
		if (tree->leftChild)
			queue.Add(tree->leftChild);
		if (tree->rightChild)
			queue.Add(tree->rightChild);
		if (queue.isEmpty())
			break;

		tree = queue.Del();
		cout << tree->data;
	}
	cout << endl;
}

template<class T>
void Tree<T>::buildTree()
{
	root = new TreeNode<T>('x');
	root->leftChild = new TreeNode<T>('a');
	root->rightChild = new TreeNode<T>('b');
	root->leftChild->leftChild = new TreeNode<T>('g');
	root->leftChild->rightChild = new TreeNode<T>('d');
	root->rightChild->leftChild = new TreeNode<T>('h');
	root->rightChild->rightChild = new TreeNode<T>('I');

}

int main()
{
	Tree<char> tree;

	tree.buildTree();
	cout << " plot the tree: \n";
	tree.Plot();
	cout << "\n\ntree's Levelorder: ";
	tree.LevelOrder();

	system("pause");
}
/*
* �G�����챵��C���ܤ覡
	node �� �T�����G data, leftChild, rightChild
	���X�G�L�X�Ҧ����`�I  ���U�ذ��k  level-order method  �i�H�̷�level�L�X�Ҧ��`�I
		�{��5.7	ex.
					   x		print out:	x a b g d h o p q
					 /   \			 
				   a       b          		queue:
				 /   \        \
			   g       d        h
					     \	  /   \
				           o p       q
*/

