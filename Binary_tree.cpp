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
	void construct_c();
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
	TreeNode<char> *nd;
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


template<class T>
void Tree<T>::construct_a()
{
	root = new TreeNode<T>('m');
	root->leftChild = new TreeNode<T>('j');
	root->rightChild = new TreeNode<T>('k');
	root->leftChild->leftChild = new TreeNode<T>('z');
	root->leftChild->rightChild = new TreeNode<T>('p');
}

template<class T>
void Tree<T>::construct_b()
{
	root = new TreeNode<T>('x');
	root->leftChild = new TreeNode<T>('a');
	root->rightChild = new TreeNode<T>('b');
	root->leftChild->leftChild = new TreeNode<T>('g');
	root->leftChild->rightChild = new TreeNode<T>('d');
	root->rightChild->leftChild = new TreeNode<T>('h');
	root->rightChild->rightChild = new TreeNode<T>('I');
	root->leftChild->rightChild->rightChild = new TreeNode<T>('o');
	root->rightChild->leftChild->leftChild = new TreeNode<T>('p');
	root->rightChild->leftChild->rightChild = new TreeNode<T>('q');
}

template<class T>
void Tree<T>::construct_c()
{
	root = new TreeNode<T>('+');
	root->leftChild = new TreeNode<T>('*');
	root->rightChild = new TreeNode<T>('/');
	root->leftChild->leftChild = new TreeNode<T>('1');
	root->leftChild->rightChild = new TreeNode<T>('2');
	root->rightChild->leftChild = new TreeNode<T>('3');
	root->rightChild->rightChild = new TreeNode<T>('-');
	root->rightChild->rightChild->leftChild = new TreeNode<T>('5');
	root->rightChild->rightChild->rightChild = new TreeNode<T>('6');
}

int main()
{
	Tree<char> treeA, treeB;

	/*........treeA.........*/
	treeA.construct_a();
	cout << "treeA's height: ";
	treeA.Height();
	cout << "\ntreeA's character ASCII sum: ";
	treeA.Sum();
	cout << "\nPlot the treeA: \n";
	treeA.Plot();
	cout << "\n\ntreeA's PreOrder: ";
	treeA.PreOrder();
	cout << "\n\ntreeA's InOrder: ";
	treeA.InOrder();
	cout << "\n\ntreeA's PostOrder: ";
	treeA.PostOrder();
	cout << "\n\ntreeA's LevelOrder: ";
	treeA.LevelOrder();

	/*........treeB.........*/
	treeB.construct_b();
	cout << "\ntreeB's height: ";
	treeB.Height();
	cout << "\ntreeB's character ASCII sum: ";
	treeB.Sum();
	cout << "\nPlot the treeB: \n";
	treeB.Plot();
	cout << "\n\ntreeB's PreOrder: ";
	treeB.PreOrder();
	cout << "\n\ntreeB's InOrder: ";
	treeB.InOrder();
	cout << "\n\ntreeB's PostOrder: ";
	treeB.PostOrder();
	cout << "\n\ntreeB's LevelOrder: ";
	treeB.LevelOrder();

	/*........treeC copy by treeB.........*/
	Tree<char> treeC(treeB);

	cout << "\nPlot the treeC: \n";
	treeC.Plot();

	/*........treeC's leftChild & rightChild change...........*/
	cout << "\nPlot the treeC's SwapTree: \n";
	treeC.SwapTree();
	treeC.Plot();

	/*........treeD's number PostOrderEval............*/
	Tree<char> treeD;
	treeD.construct_c();
	cout << "\nPlot the treeD: \n";
	treeD.Plot();
	cout << "\ntreeD's PostOrderEval: ";
	treeD.PostOrderEval();

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


