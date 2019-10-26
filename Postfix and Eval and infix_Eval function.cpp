#include <iostream>
using namespace std;

#define size 100

struct token
{
	int number;
	char op;	
	int type;	//type若為0即為number,為1則為operator
		
	void Add(int n, int t, char c)
	{
		number = n; op = c; type = t;
	}
};

template<class T>
class Bag
{
protected:
	T *array;
	int capacity;
	int top;
public:
	Bag(int bagCapacity);
	~Bag() { delete[] array; }

	bool IsEmpty();
	T Top() { return array[top]; }

	void Push(T &x);
	void Pop();
	void Pop(T *x);
};

template<class T>
Bag<T>::Bag(int bagCapacity): capacity(bagCapacity)
{
	if (capacity < 1)
		throw "Capacity must be > 0";
	array = new T[capacity];
	top = -1;
}

template<class T>
bool Bag<T>::IsEmpty()
{
	if (top == -1)
		return true;
	else
		return false;
}

template<class T>
void Bag<T>::Push(T &x)
{
	if (capacity == top + 1)
	{
		T *temp = new T[capacity *= 2];
		copy(array, array + top, temp);
		delete[] array;
		T *array = temp;
	}
	array[++top] = x;
}

template<class T>
void Bag<T>::Pop()
{
	if (IsEmpty())
		throw "Bag is empty, cannot delete";
	array[top--].~T();
}

template<class T>
void Bag<T>::Pop(T * x)
{
	if (IsEmpty())
		throw "Bag is empty, cannot delete";
	*x = array[top];
	array[top--].~T();
}

/*...................*/

int isp(char c)
{
	if (c == '*' || c == '/' || c == '%') return 1;
	else if (c == '+' || c == '-') return 2;
	else if (c == '(') return 3;
	else if (c == '$') return 4;
	else  throw "isp's character isn't in the range";
	return 10;
}

int icp(char c)
{
	if (c == '*' || c == '/' || c == '%') return 1;
	else if (c == '+' || c == '-') return 2;
	else if (c == '(') return 0;
	else  throw "icp's character isn't in the range";
	return 10;
}

/*...................*/

void Postfix(token *e)
{
	Bag<token> stack(size);
	token s[size], x;

	int p = 0, count = 0;
	for (x = e[p++]; x.op != '$'; x = e[p++])
	{
		if (x.type == 0)
		{
			s[count++].Add(x.number, x.type, x.op);
			cout << x.number;
		}
		else if (x.op == ')')
		{
			for (; stack.Top().op != '('; stack.Pop())
			{
				s[count++].Add(stack.Top().number, stack.Top().type, stack.Top().op);
				cout << stack.Top().op;
			}
			stack.Pop();   // 從堆疊中彈出  '('
		}
		else
		{
			for (; !stack.IsEmpty() && isp(stack.Top().op) <= icp(x.op); stack.Pop())
			{
				s[count++].Add(stack.Top().number, stack.Top().type, stack.Top().op);
				cout << stack.Top().op;
			}
			stack.Push(x);
		}
	}
	while (!stack.IsEmpty())
	{
		s[count++].Add(stack.Top().number, stack.Top().type, stack.Top().op);
		cout << stack.Top().op;
		stack.Pop();
	}
	s[count].Add(x.number, x.type, x.op);

	cout << endl;
}

void Eval(token *t)		//將數字已postfix的方式求出值
{
	Bag<token> stack(size);
	token y, y1, y2, y3;
	int c = 0;
	for (y = t[c++]; y.op != '$'; y = t[c++])
	{
		if (y.type == 0)
			stack.Push(y);
		else if (y.type == 1)
		{
			stack.Pop(&y1);
			stack.Pop(&y2);
			switch (y.op)
			{
			case '+': y3.number = y2.number + y1.number; break;
			case '-': y3.number = y2.number - y1.number; break;
			case '*': y3.number = y2.number * y1.number; break;
			case '/': y3.number = y2.number / y1.number; break;
			case '%': y3.number = y2.number % y1.number; break;
			default: cout << "op is fault" << endl; break;
			}
			stack.Push(y3);
		}
		else
			cout << "\n type值不正確";
	}
	stack.Pop(&y3);		//讓stack裡沒有資料 top = -1
	cout << endl << "The answer is: " << y3.number << endl;
}

void infix_Eval(token *m)
{							/*.........Postfix..........*/
	Bag<token> stack(size);
	token s[size], x;

	int p = 0, count = 0;
	for (x = m[p++]; x.op != '$'; x = m[p++])
	{
		if (x.type == 0)
			s[count++].Add(x.number, x.type, x.op);
		else if (x.op == ')')
		{
			for (; stack.Top().op != '('; stack.Pop())
			{
				s[count++].Add(stack.Top().number, stack.Top().type, stack.Top().op);
			}
			stack.Pop();   // 從堆疊中彈出  '('
		}
		else
		{
			for (; !stack.IsEmpty() && isp(stack.Top().op) <= icp(x.op); stack.Pop())
			{
				s[count++].Add(stack.Top().number, stack.Top().type, stack.Top().op);
			}
			stack.Push(x);
		}
	}
	while (!stack.IsEmpty())
	{
		s[count++].Add(stack.Top().number, stack.Top().type, stack.Top().op);
		stack.Pop();
	}
	s[count].Add(x.number, x.type, x.op);

	/*..........Eval..........*/
	token y, y1, y2, y3;
	int c = 0;
	for (y = s[c++]; y.op != '$'; y = s[c++])
	{
		if (y.type == 0)
			stack.Push(y);
		else if (y.type == 1)
		{
			stack.Pop(&y1);
			stack.Pop(&y2);
			switch (y.op)
			{
			case '+': y3.number = y2.number + y1.number; break;
			case '-': y3.number = y2.number - y1.number; break;
			case '*': y3.number = y2.number * y1.number; break;
			case '/': y3.number = y2.number / y1.number; break;
			case '%': y3.number = y2.number % y1.number; break;
			default: cout << "op is fault" << endl; break;
			}
			stack.Push(y3);
		}
		else
			cout << "\n type值不正確";
	}
	stack.Pop(&y3);		//讓stack裡沒有資料 top = -1
	cout << "The answer is: " << y3.number << endl;
}

ostream &operator<<(ostream &out, token &item)
{
	return out << item.number << "," << item.op << "," << item.type << endl;
}

int main()
{
	token str[size];

	str[0].Add(5, 0, ' ');
	str[1].Add(0, 1, '*');
	str[2].Add(6, 0, ' ');
	str[3].Add(0, 1, '/');
	str[4].Add(2, 0, ' ');
	str[5].Add(0, 1, '+');
	str[6].Add(8, 0, ' ');
	str[7].Add(0, 1, '*');
	str[8].Add(9, 0, ' ');
	str[9].Add(0, 1, '*');
	str[10].Add(0, 1, '(');
	str[11].Add(4, 0, ' ');
	str[12].Add(0, 1, '+');
	str[13].Add(3, 0, ' ');
	str[14].Add(0, 1, ')');
	str[15].Add(0, 1, '$');
	for (int i = 0; i < 16; i++)
		cout << str[i];
	
	/*只是輸出成Postfix後的樣子，str內容還是一樣*/
	cout << endl << "Postfix後: " << endl;
	Postfix(str);

	cout << endl << "Postfix後，直接輸出值:" << endl;
	infix_Eval(str);

	system("pause");
	return 0;
}

