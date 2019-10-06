#include <iostream>
using namespace std;

class Term
{
public:
	int exp;
	float coef;
};

#define max 100

class Polynomial
{
private:
	Term termArray[max];
	int capacity;
	int terms;
public:
	Polynomial();
	void NewTerm(float coef, int exp);
	
	Polynomial Add(Polynomial poly);

	int LeadExp();
	float Eval(float n);
	void print();
};

Polynomial::Polynomial()
{
	capacity = max;
	terms = 0;
}

void Polynomial::NewTerm(float coef, int exp)
{
	if (terms == capacity)
	{
		capacity *= 2;
		Term *temp = new Term[capacity];
		copy(termArray, termArray + terms, temp);
		delete[]termArray;
		Term termArray = *temp;
	}

	this->termArray[terms].coef = coef;
	this->termArray[terms++].exp = exp;
}

Polynomial Polynomial::Add(Polynomial poly)
{
	Polynomial C;
	int apos = 0, bpos = 0;
	
	while ((apos < this->terms) && (bpos < poly.terms))
	{
		if (this->termArray[apos].exp == poly.termArray[bpos].exp)
		{
			float t = this->termArray[apos].coef + poly.termArray[bpos].coef;
			if (t) C.NewTerm(t, this->termArray[apos].exp);
			apos++; bpos++;
		}
		else if (this->termArray[apos].exp > poly.termArray[bpos].exp)
		{
			C.NewTerm(this->termArray[apos].coef, this->termArray[apos].exp);
			apos++;
		}
		else if (this->termArray[apos].exp < poly.termArray[bpos].exp)
		{
			C.NewTerm(poly.termArray[bpos].coef, poly.termArray[bpos].exp);
			bpos++;
		}
	}

	for (; apos < this->terms; apos++)
		C.NewTerm(this->termArray[apos].coef, this->termArray[apos].exp);
	for (; bpos < poly.terms; bpos++)
		C.NewTerm(poly.termArray[bpos].coef, poly.termArray[bpos].exp);

	return C;
}

int Polynomial::LeadExp()
{
	return this->termArray[0].exp;
}

float Polynomial::Eval(float n)
{
	float sum = 0;
	
	for (int i = 0; i < terms; i++)
	{
		sum += (termArray[0].coef * pow(n, termArray[i].exp));
	}
	return sum;
}

void Polynomial::print()
{
	for (int i = 0; i < terms; i++)
	{
		if (i > 0)cout << (termArray[i].coef < 0 ? " - " : " + ");

		cout << termArray[i].coef;
		if (termArray[i].exp == 0);
		else if (termArray[i].exp == 1)
			cout << "x";
		else
			cout << "x^" << termArray[i].exp;

	}
	cout << endl;
}


int main()
{
	Polynomial A, B, C;

	A.NewTerm(3.0, 8);
	A.NewTerm(5.0, 2);
	A.NewTerm(6.0, 1);
	A.NewTerm(7.0, 0);

	B.NewTerm(7.0, 8);
	B.NewTerm(5.0, 2);
	B.NewTerm(9.0, 0 );

	C = A.Add(B);
	C.print();
	cout << "C's Leadexp: " << C.LeadExp() << endl;
	cout << "C's Eval: " << C.Eval(3.0) << endl;

	system("pause");
	return 0;
}

