#include <iostream>
using namespace std;

class term
{
public:
	int col, row;
	float value;
public:
	term() { col = row = 0; value = 0; }
	term(int c, int r, float v);
};

term::term(int r, int c, float v)
{
	col = c; row = r; value = v;
}

#define count 10
bool operator==(term &a, term &b)
{
	return a.row*count + a.col == b.row*count + b.col;
}

bool operator<(term &a, term &b)
{
	return a.row*count + a.col < b.row*count + b.col;
}

bool operator>(term &a, term &b)
{
	return a.row*count + a.col > b.row*count + b.col;
}


#define Max 100
template<class T>
class SparseMatrix
{
private:
	T a[Max];
	int rows, cols, terms;
public:
	SparseMatrix(int rows, int cols);

	void colSort();
	void Add(T v);
	SparseMatrix Addition(SparseMatrix b);
	SparseMatrix Multiply(SparseMatrix b);

	void Print();
};

template<class T>
SparseMatrix<T>::SparseMatrix(int rows, int cols)
{
	terms = 0;
	this->rows = rows;
	this->cols = cols;
}

template<class T>
void SparseMatrix<T>::colSort()
{
	SparseMatrix<T> temp(rows, cols);
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < terms; j++)
		{
			if (this->a[j].col == i)
			{
				term t(this->a[j].row, this->a[j].col, this->a[j].value);
				temp.Add(t);
			}
		}
	}
	*this = temp;
}

template<class T>
void SparseMatrix<T>::Add(T v)
{
	if (terms == Max - 1)
	{
		cout << "Not enough array length";
		exit(-1);
	}
	a[terms++] = v;
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::Addition(SparseMatrix b)
{
	SparseMatrix<T> C(rows, cols);

	int apos = 0, bpos = 0; 
	while ((apos < this->terms) && (bpos < b.terms))
	{
		if (this->a[apos] == b.a[bpos])
		{
			term t(this->a[apos].row, this->a[apos].col, this->a[apos].value + b.a[bpos].value);
			C.Add(t);
			apos++; bpos++;
		}
		else if (this->a[apos] < b.a[bpos])
		{
			term t(this->a[apos].row, this->a[apos].col, this->a[apos].value);
			C.Add(t);
			apos++;
		}
		else 
		{
			term t(b.a[bpos].row, b.a[bpos].col, b.a[bpos].value);
			C.Add(t);
			bpos++;
		}
	}

	for (; apos < this->terms; apos++)
	{
		term t(this->a[apos].row, this->a[apos].col, this->a[apos].value);
		C.Add(t);
		apos++;
	}
	for (; bpos < b.terms; bpos++)
	{
		term t(b.a[bpos].row, b.a[bpos].col, b.a[bpos].value);
		C.Add(t);
		bpos++;
	}
	
	return C;
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::Multiply(SparseMatrix b)
{
	SparseMatrix<T> C(this->rows, this->cols);
	b.colSort();
	
	/*rowSize[]第一個矩陣每一列有幾個數*/
	/*rowStart[]每一列從第幾個開始*/
	int *rowSize = new int[this->rows], *rowStart = new int[this->rows]{ 0 };
	for (int i = 0; i < this->rows; i++)
		rowSize[i] = 0; 
	for (int i = 0; i < this->terms; i++)	
		rowSize[this->a[i].row]++;
	for (int i = 1; i < cols; i++)
		rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
	/*colSize[]第二個矩陣每一行有幾個數*/
	/*colStart[]每一行從第幾個開始*/
	int *colSize = new int[this->cols], *colStart = new int[this->cols]{ 0 };
	for (int i = 0; i < this->cols; i++)
		colSize[i] = 0;	
	for (int i = 0; i < b.terms; i++)
		colSize[b.a[i].col]++;
	for (int i = 1; i < cols; i++)
		colStart[i] = colStart[i - 1] + colSize[i - 1];

	int apos = 0, bpos = 0;	   //將乘完相加的數放在指定位置
	/*有幾列幾行就要乘幾次，如:3列3行要乘9次*/
	for (int i = 0; i < this->rows; i++)	
	{	
		for (int j = 0; j < this->cols; j++)
		{
			float sum = 0;
			for (int k = rowStart[i]; k < rowSize[i] + rowStart[i]  ; k++)
				for(int m = colStart[j]; m < colSize[j] + colStart[j]; m++)
					if (this->a[k].col == b.a[m].row)
					{
						apos = this->a[k].row;
						bpos = b.a[m].col;
						sum += this->a[k].value * b.a[m].value;
					}
			if (sum)
			{
				term temp(apos, bpos, sum);
				C.Add(temp);
			}
		}
	}

	delete[] rowSize, colSize, rowStart, colStart;
	return C;
}

template<class T>
void SparseMatrix<T>::Print()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			float sum = 0;
			for (int t = 0; t < terms; t++)
			{
				if (a[t].row == i && a[t].col == j)
				{
					sum = a[t].value;
					break;
				}
			}
			cout << sum << " ";
		}
		cout << endl;
	}
}

template<class T>
SparseMatrix<T> operator+(SparseMatrix<T> & a, SparseMatrix<T> & b)
{
	return a.Addition(b);
}

template<class T>
SparseMatrix<T> operator*(SparseMatrix<T> & a, SparseMatrix<T> & b)
{
	return a.Multiply(b);
}

int main()
{
	SparseMatrix<term> A(3, 3), B(3, 3), C(3, 3), D(3, 3);
	term A1(0, 0, 4.0);
	term A2(1, 1, 7.0);
	term A3(2, 0, 7.0);
	term A4(2, 2, 9.0);
	term B1(0, 0, 4.0);
	term B2(1, 0, 5.0);
	term B3(1, 2, 3.0);
	term B4(2, 0, 8.0);
	A.Add(A1);
	A.Add(A2);
	A.Add(A3);
	A.Add(A4);
	B.Add(B1);
	B.Add(B2);
	B.Add(B3);
	B.Add(B4);
	
	cout << "A's matrix:" << endl;
	A.Print();
	cout << endl << "B's matrix:" << endl;
	B.Print();

	cout << endl << "A + B 's matrix: " << endl;
	C = A + B;
	C.Print();

	cout << endl << "A * B 's matrix: " << endl;
	D = A * B;
	D.Print();

	system("pause");
}


