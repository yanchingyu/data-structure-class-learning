#include <iostream>
using namespace std;

template<class T>
class Bag
{
private:
	T *array;
	int capacity;
	int top;
public:
	Bag() {int capacity = 0; }
	Bag(int cap);

	bool isEmpty();

	void push(T &x);
	T Top();
	void pop(T *x);
};

template<class T>
Bag<T>::Bag(int cap) : capacity(cap)
{
	if (capacity < 1)
		throw "Capacity must be > 0";
	array = new T[capacity];
	top = -1;
}

template<class T>
bool Bag<T>::isEmpty()
{
	if (top == -1)
		return true;
	else
		return false;
}

template<class T>
void Bag<T>::push(T & x)
{
	if (capacity == top + 1)
	{
		cout << "push so much";
		exit(-1);
	}
	array[++top] = x;
}

template<class T>
T Bag<T>::Top()
{
	return array[top];
}

template<class T>
void Bag<T>::pop(T *x)
{
	if (isEmpty()) throw "Bag is empty, cannot delete";

	*x = array[top--];
}

template<class T>
class Stack : public Bag<T>
{
public:
	Stack(int cap) : Bag<T>(cap) {}
};

int main()
{
	try {
		/*數字倒述*/
		Bag<int> A(100);
		int iv;
		for (int i = 1; i <= 100; i++)
			A.push(i);
		cout << "數字倒述:" << endl;
		for (int i = 0; i < 100; i++)
		{
			A.pop(&iv);
			cout << iv << " ";
		}
		cout << endl;
		
		/*用另一個class繼承Bag做出倒述*/
		Stack<char> B(100);
		char cv;
		string s = "Hello World!";
		for (int i = 0; i < s.length(); i++)
			B.push(s.at(i));
		cout << "文字倒述:" << endl;
		for (int i = 0; i < s.length(); i++)
		{
			B.pop(&cv);
			cout << cv << " ";
		}
		cout << endl;
	}
	catch (char *msg)
	{
		cout << msg;
	}
	

	system("pause");
}


