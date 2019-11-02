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
	Bag(int BagCapacity = 10);

	bool IsEmpty() const;

	void Push(T &x);
	void Pop();
	void Pop(T *x);

	T Top() { return array[top]; }
};

template<class T>
Bag<T>::Bag(int BagCapacity) : capacity(BagCapacity)
{
	if (capacity < 1) throw "capacity must be > 0";
	array = new T[capacity];
	top = -1;
}

template<class T>
bool Bag<T>::IsEmpty() const
{
	if (top == -1) return true;
	else return false;
}

template<class T>
void Bag<T>::Push(T &x)
{
	if (capacity == top + 1)
	{
		T *temp = new T[capacity *= 2];
		copy(array, array + capacity, temp);
		delete[] array;
		array = temp;
	}
	array[++top] = x;
}

template<class T>
void Bag<T>::Pop()
{
	if (IsEmpty()) throw "Bag is empty, cannot delete";
	array[top--].~T();
}

template<class T>
void Bag<T>::Pop(T * x)
{
	if (IsEmpty()) throw "Bag is empty, cannot delete";
	*x = array[top];
	array[top--].~T();
}

/* ...................Stack........................ */
template<class T>
class Stack : public Bag<T>
{
public:
	Stack(int cap)
	{
		Bag<T>();
	}
};

// ...................... maze program
enum Direction { N, NE, E, SE, S, SW, W, NW };

struct offest
{
	int a, b;
};

offest Move[8];		// 八個位置對照著 enum Direction

class Items
{
public:
	int x, y, dir;		// x為row, y為col, dir為方向
	Items() { x = 0; y = 0; dir = 0; };
	Items(int a, int b, int c);
};

Items::Items(int a, int b, int c)
{
	x = a; y = b; dir = c;
}

ostream& operator<<(ostream& os, Items& t)
{
	return os << t.x << ":" << t.y << endl;
}

const int m = 4, p = 4;
int mark[m + 2][p + 2];
int maze[][p + 2] = { { 1,1,1,1,1,1 },
					  { 1,0,0,0,1,1 },
					  { 1,0,1,1,0,1 },
					  { 1,0,1,0,1,1 },
					  { 1,1,1,1,0,1 },
					  { 1,1,1,1,1,1 }
};	//周圍的1為迷宮的牆壁

void print_path(Stack<Items> stack)
{
	while (!stack.IsEmpty())
	{
		cout << stack.Top().x << ":" << stack.Top().y << endl;
		stack.Pop();
	}
}

void Path(const int m, const int p)
{
	// 從 (1, 1) 開始
	for (int i = 0; i < m + 2; i++)
		for (int j = 0; j < p + 2; j++)
			mark[i][j] = 0;

	Stack<Items> stack(m*p); 
	Items temp(1, 1, 0);	// 設定 temp.x、temp.y、與temp.dir	
	stack.Push(temp);

	{
		Move[0].a = -1; Move[0].b = 0;	//N
		Move[1].a = -1; Move[1].b = 1;	//NE
		Move[2].a = 0; Move[2].b = 1;	//E
		Move[3].a = 1; Move[3].b = 1;	//SE
		Move[4].a = 1; Move[4].b = 0;	//S
		Move[5].a = 1; Move[5].b = -1;	//SW
		Move[6].a = 0; Move[6].b = -1;	//W
		Move[7].a = -1; Move[7].b = -1;	//NW
	}

	while (!stack.IsEmpty())
	{
		temp = stack.Top();
		stack.Pop();
		int x = temp.x, y = temp.y, dir = temp.dir;
		cout << "one pop: " << x << " " << y << " " << dir << endl;

		while (dir < 8)
		{
			cout << "one i & j: " << x << " " << y << " " << dir << endl;
			int g = x + Move[dir].a;
			int h = y + Move[dir].b;

			if (g == m && h == p)  // 抵達出口
			{
				Stack<Items> stk(m*p);
				while (!stack.IsEmpty())
				{
					temp = stack.Top();
					stack.Pop();
					stk.Push(temp);
				}
				while (!stk.IsEmpty())
				{
					stk.Pop(&temp);
					cout << temp;
				}
				cout << x << ":" << y << endl;
				cout << g << ":" << h << endl;
				return;
			}
			if (!maze[g][h] && !mark[g][h])
			{
				mark[g][h] = 1;
				temp.x = x; temp.y = y; temp.dir = dir + 1;
				stack.Push(temp); // 加入堆疊
				x = g; y = h; dir = 0; // 移到 (g, h)
			}
			else dir++;	// 試下一個方向
		}
	}
	cout << "No path in maze." << endl;
}

int main()
{
	Path(m, p);

	system("pause");
}


