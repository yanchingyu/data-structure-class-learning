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
Queue<T>::Queue(int cap) :capacity(cap)
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
	TreeNode(T d, TreeNode<T> *l, TreeNode<T> *r);
private:
	T data;
	int value;
	TreeNode<T> *leftChild, *rightChild;
};

template<class T>
TreeNode<T>::TreeNode(T e)
{
	data = e;
	value = e - '0';
	leftChild = rightChild = 0;
}

template<class T>
TreeNode<T>::TreeNode(T d, TreeNode<T>* l, TreeNode<T>* r)
{
	data = d;
	leftChild = l;  rightChild = r;
}

/*...........................class Tree.............................*/
template<class T>
class Tree
{
public:
	Tree() { root = 0; }
	Tree(Tree<T> &p);

	TreeNode<T> * Copy(TreeNode<T> *originNode);
	void Insert(T e);
	void Plot();

	void PreOrder();
	void PreOrder(TreeNode<T> *p);
	void InOrder();
	void InOrder(TreeNode<T> *p);
	void PostOrder();
	void PostOrder(TreeNode<T> *p);
	void PostOrderEval();
	void PostOrderEval(TreeNode<T> *p);
	void LevelOrder();

	void SwapTree();
	TreeNode<T> * SwapTree(TreeNode<T> *p);

	void Height();			//用PreOrder方式
	int Height(TreeNode<T> *pt);
	void Sum();				//用PreOrder方式
	int Sum(TreeNode<T> *pt);

	void construct_a();
	void construct_b();
private:
	TreeNode<T> *root;
};

template<class T>
Tree<T>::Tree(Tree<T>& p)
{
	root = Copy(p.root);
}

template<class T>
TreeNode<T> *Tree<T>::Copy(TreeNode<T>* originNode)		//PreOrder方式Copy
{
	if (!originNode) return 0;
	return new TreeNode<T>(originNode->data,
		Copy(originNode->leftChild),
		Copy(originNode->rightChild));
}

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
			if (tmp->data <= pt->data)		/*只要tmp如果比pt小就往左，沒辦法往左就給值*/
			{
				if (!pt->leftChild)
				{
					pt->leftChild = tmp;
					break;
				}
				pt = pt->leftChild;
			}
			else							/*只要tmp如果比pt大就往右，沒辦法往右就給值*/
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

/*....................by teacher's 每個葉子之間的空格表示方式.........*/

struct tmpT
{
	TreeNode<int> *nd;
	int v1, v2;
};

#define MAX_LEVEL 6
#define RESOLUTION 2
#define LEFT_MARGINE 1
template<class T>
void Tree<T>::Plot()			//輸出樹狀圖
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
	cout << endl;
}


template<class T>
void Tree<T>::PreOrder()
{
	PreOrder(root);
}

template<class T>
void Tree<T>::PreOrder(TreeNode<T>* p)
{
	if (p)
	{
		cout << p->data << " ";
		PreOrder(p->leftChild);
		PreOrder(p->rightChild);
	}
}

template<class T>
void Tree<T>::InOrder()
{
	InOrder(root);
}

template<class T>
void Tree<T>::InOrder(TreeNode<T>* p)
{
	if (p)
	{
		InOrder(p->leftChild);
		cout << p->data << " ";
		InOrder(p->rightChild);
	}
}

template<class T>
void Tree<T>::PostOrder()
{
	PostOrder(root);
}

template<class T>
void Tree<T>::PostOrder(TreeNode<T>* p)
{
	if (p)
	{
		PostOrder(p->leftChild);
		PostOrder(p->rightChild);
		cout << p->data << " ";
	}
}

template<class T>
void Tree<T>::PostOrderEval()
{
	PostOrderEval(root);
	cout << root->value << endl;
}

template<class T>
void Tree<T>::PostOrderEval(TreeNode<T>* p)
{
	if (p)
	{
		PostOrderEval(p->leftChild);
		PostOrderEval(p->rightChild);
		switch (p->data)
		{
		case '+': p->value = p->leftChild->value + p->rightChild->value; break;
		case '-': p->value = p->leftChild->value - p->rightChild->value; break;
		case '*': p->value = p->leftChild->value * p->rightChild->value; break;
		case '/': p->value = p->leftChild->value / p->rightChild->value; break;
		case '%': p->value = p->leftChild->value % p->rightChild->value; break;
		default: break;
		}
	}
}

template<class T>
void Tree<T>::LevelOrder()
{
	Queue<TreeNode<T>*> queue(20);
	TreeNode<T> *tree = root;

	cout << tree->data << " ";
	while (tree)
	{
		if (tree->leftChild)
			queue.Add(tree->leftChild);
		if (tree->rightChild)
			queue.Add(tree->rightChild);
		if (queue.isEmpty())
			break;

		tree = queue.Del();
		cout << tree->data << " ";
	}
	cout << endl;
}


template<class T>
void Tree<T>::SwapTree()
{
	root = SwapTree(root);
}

template<class T>
TreeNode<T> * Tree<T>::SwapTree(TreeNode<T>* p)
{
	if (!p)
		return 0;
	return new TreeNode<T>(p->data, SwapTree(p->rightChild), SwapTree(p->leftChild));
}


template<class T>
void Tree<T>::Height()
{
	cout << Height(root);
}

template<class T>
int Tree<T>::Height(TreeNode<T>* pt)		//height(root) = max{ height(L), height(R) } + 1				
{
	int height = 0;

	if (pt == 0) return 0;
	else
	{
		int left_height = Height(pt->leftChild);
		int right_height = Height(pt->rightChild);
		if (left_height > right_height)
			height = left_height;
		else
			height = right_height;
		return height + 1;
	}
}

template<class T>
void Tree<T>::Sum()
{
	cout << Sum(root);
}

template<class T>
int Tree<T>::Sum(TreeNode<T>* pt)
{
	int total = 0;
	if (pt)
	{
		total = Sum(pt->leftChild) + Sum(pt->rightChild) + pt->data;
	}
	return total;
}


/*insert數字當數字比root小就往左移，比root大往右移*/
template<class T>
void Tree<T>::construct_a()
{
	this->Insert(4);
	this->Insert(6);
	this->Insert(5);
	this->Insert(9);
	this->Insert(7);
	this->Insert(11);
	this->Insert(2);
	this->Insert(1);
}

template<class T>
void Tree<T>::construct_b()
{
	this->Insert(8);
	this->Insert(4);
	this->Insert(12);
	this->Insert(2);
	this->Insert(5);
	this->Insert(3);
	this->Insert(10);
	this->Insert(11);
	this->Insert(14);
	this->Insert(13);
}

int main()
{
	Tree<int> treeA, treeB;
	
	/*.................treeE................*/
	cout << "treeE the Plot:";
	treeA.construct_a();
	treeA.Plot();

	/*.................treeF................*/
	cout << "\n\ntreeF the Plot:";
	treeB.construct_b();
	treeB.Plot();

	system("pause");
}
/*
* 二元樹的鏈接串列表示方式
	node 有 三個欄位： data, leftChild, rightChild
	走訪：印出所有的節點  有各種做法  level-order method  可以依照level印出所有節點
		程式5.7	ex.
					   x		print out:	x a b g d h o p q
					 /   \
				   a       b          		queue:
				 /   \        \
			   g       d        h
						 \	  /   \
						   o p       q
*/

/*...Plot()自己算的空格公式  3*(pow(2, height - 1) - 1) + pow(2, height),  3為最下一層三個空格、 height為總共有幾層*/


