#include <iostream>
using namespace std;

class Term
{
public:
	Term() { coef = 0; exp = 0; };
	Term(float coef, int exp) { this->coef = coef; this->exp = exp; };

	float getCoef() { return coef; };
	int getExp() { return exp; };

	friend ostream& operator<<(ostream& out, Term&t);
private:
	float coef;
	int exp;
};

ostream & operator<<(ostream & out, Term &t)
{
	out << t.coef;

	if (t.exp == 0)
		return out;
	else if (t.exp == 1)
		return out << "x";
	else
		return out << "x^" << t.exp;
}

#define max 100

template<class T>
class arrayt
{
public:
	arrayt() { n = 0; };
	
	void Add(T v);		//加入到最後一位
	arrayt<T> Mult(arrayt<T> v);

	void Print();
private:
	T a[max];
	int n;
};



template<class T>
void arrayt<T>::Add(T v)
{
	if (n == max)
	{
		int capacity = max;
		capacity *= 2;
		Term *temp = new Term[capacity];
		delete[]a;
		T a = *temp;
	}
	a[n++] = v;
}

template<class T>
arrayt<T> arrayt<T>::Mult(arrayt<T> v)
{
	arrayt<T> C;

	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < v.n; j++)
		{
			Term temp(this->a[i].getCoef() * v.a[j].getCoef(), this->a[i].getExp() + v.a[j].getExp());
			C.Add(temp);
		}
	}

	return C;
}

template<class T>
void arrayt<T>::Print()
{
	cout << "A(x) * B(x) = ";
	for (int i = 0; i < n; i++)
	{
		if (i > 0)
			cout << (a[i].getCoef() < 0 ? "-" : "+ ");

		cout << a[i] << " ";
	}
	cout << endl;
}


int main(void)
{
	arrayt<Term> A, B, C;
	Term A1(3.0, 4);
	Term A2(6.0, 1);
	Term B1(4.0, 1);
	Term B2(7.0, 0);

	A.Add(A1);
	A.Add(A2);
	B.Add(B1);
	B.Add(B2);

	C = A.Mult(B);
	C.Print();

	system("pause");
	return 0;
}

