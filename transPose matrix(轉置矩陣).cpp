#include <iostream>
using namespace std;

class term {
public:
	int row, col;
	float value;
	
	term()
	{
		row = col = 0;
		value = 0;
	}
	term(int row, int col, float value)
	{
		this->row = row;
		this->col = col;
		this->value = value;
	}

};

#define count 10
bool operator>(term& t1, term& t2)
{
	return t1.row*count + t1.col > t1.row*count + t2.col;
}

bool operator<(term& t1, term& t2)
{
	return t1.row*count + t1.col < t1.row*count + t2.col;
}

bool operator==(term& t1, term& t2)
{
	return t1.row*count + t1.col == t1.row*count + t2.col;
}

#define Max 100
template<class T>
class SparseMatrix {
private:
	T a[Max];
	int n, rows, cols;
public:
	SparseMatrix() { n = 0; }
	SparseMatrix(int r, int c) { rows = r; cols = c; n = 0; }

	void Sort();
	void Add(T v);
	void Print();

	SparseMatrix transPose();
};

template<class T>
void SparseMatrix<T>::Sort()
{
	for (int i = 0; i < n; i++)
	{
		int j = i;
		//找出a[i]到a[n-1]中最小的一個整數
		for (int k = i + 1; k < n; k++)
			if (a[k] < a[j]) j = k;
		swap(a[i], a[j]);
	}
}

template<class T>
void SparseMatrix<T>::Add(T v)
{
	if (n == Max - 1)
	{
		cout << "Not enough array length";
		exit(-1);
	}
	a[n++] = v;
}

template<class T>
void SparseMatrix<T>::Print()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			float sum = 0;
			for (int k = 0; k < n; k++)				//迴圈跑a陣列
			{
				if (a[k].row == i && a[k].col == j)
					sum = a[k].value;
			}
			cout << sum << " ";
		}
		cout << endl;
	}
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::transPose()
{
	SparseMatrix<T> temp(cols, rows);		//將原本的cols and rows 反過來

	for (int i = 0; i < cols; i++)			//用行來轉置
	{
		for (int j = 0; j < n; j++)
		{
			if (this->a[j].col == i)
			{
				term t(i, this->a[j].row, this->a[j].value);
				temp.Add(t);
			}
		}
	}

	return temp;
}



int main()
{
	SparseMatrix<term> A(4, 3);
	term A1(0, 0, 4.0);
	term A2(1, 1, 7.0);
	term A3(2, 2, 7.0);
	term A4(2, 0, 9.0);
	term A5(3, 1, 5.0);
	A.Add(A1);
	A.Add(A2);
	A.Add(A3);
	A.Add(A4);
	A.Add(A5);

	A.Sort();
	cout << "A's matrix" << endl;
	A.Print();
	
	cout << "A' transPose matrix" << endl;
	A = A.transPose();
	A.Print();

	system("pause");
}


