#include <iostream>
using namespace std;

template<class T>
class Queue
{
private:
	int front, rear;
	T *array;
	int capacity;
public:
	Queue(int cap);

	void Add(T x);
	T Del();
	bool isEmpty();
};

template<class T>
Queue<T>::Queue(int cap)
{
	front = rear = 0;
	array = new T[capacity = cap];
}

template<class T>
void Queue<T>::Add(T x)
{
	if (++rear % capacity == front)
		cout << "Queue is full";
	else
		array[rear] = x;
}

template<class T>
T Queue<T>::Del()
{
	if (front == rear)
		cout << "Queue is empty";
	else
	{
		front = ++front % capacity;
		return array[front];
	}
}

template<class T>
bool Queue<T>::isEmpty()
{
	if (front == rear)
		return true;
	else
		return false;
}

#define size 51
int main()
{
	Queue<int> num(size);

	for (int i = 1; i < size; i++)
	{
		num.Add(i);
	}
	for (int i = 0; i < size; i++)
	{
		if (num.isEmpty())
			break;
		else
			cout << num.Del() << " ";
	}

	system("pause");
}


