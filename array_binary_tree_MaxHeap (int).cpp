#include <iostream>
using namespace std;

template<class T>
class array_binary_tree
{
public:
	array_binary_tree(int cap);

	void Push(const T &e);

	void PreOrder();
	void PreOrder(int p);
	void InOrder();
	void InOrder(int p);
	void PostOrder();
	void PostOrder(int p);
	void LevelOrder();

	void Build_treeA();
private:
	T *heap;
	int heapSize;
	int capacity;
};


template<class T>
array_binary_tree<T>::array_binary_tree(int cap) : capacity(cap)
{
	heap = new T[capacity];
	for (int i = 0; i < capacity; i++)
		heap[i] = 0;
	heapSize = 0;
}

template<class T>
void array_binary_tree<T>::Push(const T & e)			//MaxHeap
{ // 加入元素 e 到最大堆積中。			
	if (heapSize == capacity)
	{
		cout << "heap is full" << endl;
	}
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < e)	//若子節點(newNode)比父節點大，兩者交換
	{
		heap[currentNode] = heap[currentNode / 2];		
		currentNode /= 2;
	}
	heap[currentNode] = e;
}

template<class T>
void array_binary_tree<T>::PreOrder()
{
	PreOrder(1);
}

template<class T>
void array_binary_tree<T>::PreOrder(int p)
{
	cout << heap[p] << " ";
	if (heap[p * 2] != 0) PreOrder(2 * p);
	if (heap[p * 2 + 1] != 0) PreOrder(2 * p + 1);
}

template<class T>
void array_binary_tree<T>::InOrder()
{
	InOrder(1);
}

template<class T>
void array_binary_tree<T>::InOrder(int p)
{
	if (heap[p * 2] != 0) InOrder(2 * p);
	cout << heap[p] << " ";
	if (heap[p * 2 + 1] != 0) InOrder(2 * p + 1);
}

template<class T>
void array_binary_tree<T>::PostOrder()
{
	PostOrder(1);
}

template<class T>
void array_binary_tree<T>::PostOrder(int p)
{
	if (heap[p * 2] != 0) PostOrder(2 * p);
	if (heap[p * 2 + 1] != 0) PostOrder(2 * p + 1);
	cout << heap[p] << " ";
}

template<class T>
void array_binary_tree<T>::LevelOrder()
{
	for (int i = 1; i <= heapSize; i++)
	{
		cout << heap[i] << " ";
	}
	cout << endl;
}

template<class T>
void array_binary_tree<T>::Build_treeA()
{
	this->Push(4);
	this->Push(9);
	this->Push(3);
	this->Push(5);
	this->Push(11); 
	this->Push(13);
	this->Push(6);
}

int main()
{
	array_binary_tree<int> treeA(100);
	treeA.Build_treeA();

	cout << "treeA's array int PreOrder: ";
	treeA.PreOrder();
	cout << "\n\ntreeA's array int InOrder: ";
	treeA.InOrder();
	cout << "\n\ntreeA's array int PostOrder: ";
	treeA.PostOrder();
	cout << "\n\ntreeA's array int LevelOrder: ";
	treeA.LevelOrder(); 


	system("pause");
}