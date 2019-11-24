#include <iostream>
using namespace std;

struct Triple{ int row, col, value; };
class Matrix;

class MatrixNode
{
	friend class Matrix;
	friend istream& operator>>(istream& in, Matrix &matrix);
private:
	MatrixNode *down, *right;
	bool head;
	union			//union裡的資料共用一個儲存位置
	{
		MatrixNode *next;			
		Triple triple;
	};
	MatrixNode(bool b, Triple *t);
};

MatrixNode::MatrixNode(bool b, Triple *t)
{
	head = b;
	if (b)
	{
		right = down = this;
		next = this;
	}
	else
		triple = *t;
}

class Matrix
{
	friend istream& operator>>(istream& in, Matrix &matrix);
public:
	void Print();
	void Print_normal_matrix();
private:
	MatrixNode *headnode;
};

void Matrix::Print()
{
	for (MatrixNode *hpt = headnode->right; hpt != headnode; hpt = hpt->next)
	{
		for (MatrixNode *pt = hpt->right; pt != hpt; pt = pt->right)
		{
			cout << pt->triple.row << ":" << pt->triple.col << " " << pt->triple.value << "   ";
		}
	}
}

void Matrix::Print_normal_matrix()
{
	int rown = headnode->triple.row;
	int coln = headnode->triple.col;

	MatrixNode *hpt = headnode->right, *pt = hpt->right;
	for (int i = 0; i < rown; i++)
	{
		for (int j = 0; j < coln; j++)
		{
			if (i == pt->triple.row && j == pt->triple.col)
			{
				cout << pt->triple.value << " ";
				pt = pt->right;
			}
			else
				cout << 0 << " ";
		}
		cout << endl;
		hpt = hpt->next;
		pt = hpt->right;
	}
}

int max(int row, int col)
{
	return (row > col) ? row : col;
}

istream& operator>>(istream& in, Matrix &matrix)
{
	Triple s;
	in >> s.row >> s.col >> s.value;		// 矩陣維度	s.value為稀疏矩陣的非0項
	int p = max(s.row, s.col);
	
	matrix.headnode = new MatrixNode(false, &s);
	if (p == 0)
	{
		matrix.headnode->right = matrix.headnode;
		return in;
	}

	/* ...至少有一個列或行...*/
	MatrixNode **head = new MatrixNode *[p];
	for (int i = 0; i < p; i++)
		head[i] = new MatrixNode(true, 0);
	
	int currentRow = 0;
	MatrixNode *last = head[0];		// 目前這一列的最後一個節點
	for (int i = 0; i < s.value; i++)
	{
		Triple t;
		in >> t.row >> t.col >> t.value;
		if (t.row > currentRow)
		{
			last->right = head[currentRow];
			currentRow = t.row;
			last = head[currentRow];
		}
		last = last->right = new MatrixNode(false, &t);		// 鏈結一個新節點到目前的列
		head[t.col]->next = head[t.col]->next->down = last;		// 鏈結到行串列
	}

	last->right = head[currentRow];		// 關掉最後一列
	for (int i = 0; i < s.col; i++)		// 關掉所有的行串列
		head[i]->next->down = head[i + 1];	
	// 把標頭節點鏈結在一起
	for (int i = 0; i < p; i++)
		head[i]->next = head[i + 1];
	head[p - 1]->next = matrix.headnode;
	matrix.headnode->right = head[0];
	delete[] head;
	return in;
}

int main()
{
	Matrix m;
	cin >> m;
	cout << "end of execution. ";
	m.Print();
	cout << endl;
	m.Print_normal_matrix();

	system("pause");
}

