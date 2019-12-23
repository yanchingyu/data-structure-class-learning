#include <iostream>
using namespace std;

template<class T>
class array_binary_tree
{
public:
	array_binary_tree();

	void PreOrder();
	void PreOrder(int p);
	void InOrder();
	void InOrder(int p);
	void PostOrder();
	void PostOrder(int p);
	void LevelOrder();

	void Build_treeA();
private:
	T ar[100];
	int n;
};


template<class T>
array_binary_tree<T>::array_binary_tree()
{
	for (int i = 0; i < 100; i++) ar[i] = '0';
	n = 0;
}

template<class T>
void array_binary_tree<T>::PreOrder()
{
	PreOrder(1);
}

template<class T>
void array_binary_tree<T>::PreOrder(int p)
{
	cout << ar[p] << " ";
	if (ar[p*2] != '0') PreOrder(2 * p);
	if (ar[p*2 + 1] != '0') PreOrder(2 * p + 1);
}

template<class T>
void array_binary_tree<T>::InOrder()
{
	InOrder(1);
}

template<class T>
void array_binary_tree<T>::InOrder(int p)
{
	if (ar[p * 2] != '0') InOrder(2 * p);
	cout << ar[p] << " ";
	if (ar[p * 2 + 1] != '0') InOrder(2 * p + 1);
}

template<class T>
void array_binary_tree<T>::PostOrder()
{
	PostOrder(1);
}

template<class T>
void array_binary_tree<T>::PostOrder(int p)
{
	if (ar[p * 2] != '0') PostOrder(2 * p);
	if (ar[p * 2 + 1] != '0') PostOrder(2 * p + 1);
	cout << ar[p] << " ";
}

template<class T>
void array_binary_tree<T>::LevelOrder()
{
	for (int i = 1; i <= n; i++)
	{
		cout << ar[i] << " ";
	}
}

template<class T>
void array_binary_tree<T>::Build_treeA()
{
	ar[1] = 'a'; ar[2] = 'b'; ar[3] = 'c';
	ar[4] = '0'; ar[5] = '0'; ar[6] = 'd';
	ar[7] = 'e'; ar[8] = '0'; ar[9] = '0';
	ar[10] = '0'; ar[11] = '0'; ar[12] = 'w';
	ar[n = 13] = 'z';
}



int main()
{
	array_binary_tree<char> treeA;
	treeA.Build_treeA();
	cout << "treeA's array PreOrder: ";
	treeA.PreOrder();
	cout << "\n\ntreeA's array InOrder: ";
	treeA.InOrder();
	cout << "\n\ntreeA's array PostOrder: ";
	treeA.PostOrder();

	system("pause");
}