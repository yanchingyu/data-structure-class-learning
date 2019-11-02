#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>

using namespace std;

class term {
public:
	int exp;
	float coef;

	friend bool operator>(term&, term&);
	friend bool operator<(term&, term&);
};

bool operator>(term& t1, term& t2) {
	return t1.exp > t2.exp;
}

bool operator<(term& t1, term& t2) {
	return t1.exp < t2.exp;
}

class Polynomial {
private:
	term termArray[100];
	int terms, capacity;
public:
	Polynomial();

	Polynomial Substract(Polynomial poly);

	Polynomial Add(Polynomial poly);
	// �^�� *this�Ppoly��Ӧh�������M�C

	Polynomial Mult(Polynomial poly);
	// �^�� *this�Ppoly��Ӧh�������n�C

	void ReverseSort();

	float Eval(float f);
	// �D�X��h���� *this�� f�ɪ��ȨåB�^�ǥ������G�C

	void NewTerm(float coef, int exp);
	int LeadExp();

	void Print();
	friend ostream& operator<<(ostream& os, Polynomial &t);
};

Polynomial::Polynomial() {
	capacity = 100;
	terms = 0;
}

void Polynomial::Print() {
	for (int i = 0; i < terms; i++) {
		//if(i > 0) cout << " " << (termArray[i].coef > 0 ? '+' : '-') << " ";
		cout << termArray[i].coef;

		if (termArray[i].exp > 1)
			cout << "x^" << termArray[i].exp << " + ";
		else if (termArray[i].exp == 1)
			cout << "x + ";
	}
	cout << endl;
}

Polynomial Polynomial::Substract(Polynomial b)
{
	Polynomial c;
	int aPos = 0, bPos = 0;
	while ((aPos < terms) && (bPos < b.terms))
		if (termArray[aPos].exp == b.termArray[bPos].exp) {
			float t = termArray[aPos].coef - b.termArray[bPos].coef;
			if (t) c.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) {
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	// �� *this���ѤU�������[�i��
	for (; aPos < terms; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	// �� b(x) ���ѤU�������[�i��
	for (; bPos < b.terms; bPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}

Polynomial Polynomial::Add(Polynomial b)
{// �^�Ǧh���� *this�Pb���M
	Polynomial c;
	int aPos = 0, bPos = 0;
	while ((aPos < terms) && (bPos < b.terms))
		if (termArray[aPos].exp == b.termArray[bPos].exp) {
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) c.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) {
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	// �� *this���ѤU�������[�i��
	for (; aPos < terms; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	// �� b(x) ���ѤU�������[�i��
	for (; bPos < b.terms; bPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}

Polynomial Polynomial::Mult(Polynomial v)
{
	Polynomial cc;
	Polynomial aa = *this;

	for (int i = 0; i < terms; i++)
	{
		for (int j = 0; j < v.terms; j++)
			cc.NewTerm(termArray[i].coef * v.termArray[j].coef, termArray[i].exp + v.termArray[j].exp);
		
	}
	cc.ReverseSort();
	Polynomial dd;

	int j;
	for (j = 0; j < cc.terms - 1; j++)
	{
		if (cc.termArray[j].exp == cc.termArray[j + 1].exp)
		{
			int k = j;
			float f;
			for(k; cc.termArray[k].exp == cc.termArray[k + 1].exp; k++)
				f = cc.termArray[k].coef + cc.termArray[k + 1].coef;
			
			dd.NewTerm(f, cc.termArray[j].exp);
			j = k;
		}
		else
		{
			dd.NewTerm(cc.termArray[j].coef, cc.termArray[j].exp);
		}
	}

	dd.NewTerm(cc.termArray[j].coef, cc.termArray[j].exp);
	return dd;
}

void Polynomial::ReverseSort()
{ //��a[0]��a[n-1]�`�@n�ӼƥH���W�����ǱƦC
	for (int i = 0; i < terms; i++)
	{
		int j = i;
		//��Xa[i]��a[n-1]���̤p���@�Ӿ��
		for (int k = i + 1; k < terms; k++)
			if (termArray[k].exp > termArray[j].exp) j = k;
		
		term temp = termArray[i];
		termArray[i] = termArray[j];
		termArray[j] = temp;
	}
}

float Polynomial::Eval(float f)
{
	float sum = 0;

	for (int i = 0; i < terms; i++)
	{
		sum += (this->termArray[i].coef * pow(f, this->termArray[i].exp));
	}
	return sum;
}

void Polynomial::NewTerm(const float theCoeff, const int theExp)
{// �btermArray�����ݥ[�J�@�ӷs��
	/*
	if (terms == capacity)
	{// �NtermArray���e�q�[��
		capacity *= 2;
		term *temp = new term[capacity];  // �s�}�C
		copy(termArray, termArray + terms, temp);
		delete [] termArray ;              // �����ª��O����
		termArray = temp;
	}
	*/
	termArray[terms].coef = theCoeff;
	termArray[terms++].exp = theExp;
}

int Polynomial::LeadExp()
{
	return this->termArray[0].exp;
}

Polynomial operator-(Polynomial & x, Polynomial &y)
{
	return x.Substract(y);
}

Polynomial operator*(Polynomial & x, Polynomial &y)
{
	return x.Mult(y);
}

ostream& operator<<(ostream& os, Polynomial &t)
{
	for (int i = 0; i < t.terms; i++) {
		//if(i > 0) cout << " " << (termArray[i].coef > 0 ? '+' : '-') << " ";
		os << t.termArray[i].coef;

		if (t.termArray[i].exp > 1)
			os << "x^" << t.termArray[i].exp << " + ";
		else if (t.termArray[i].exp == 1)
			os << "x + ";
	}
	os << endl;
	return os;
}

int main() {
	Polynomial aa, bb, cc, dd;
	aa.NewTerm(7.0, 11);
	aa.NewTerm(3.0, 8);
	aa.NewTerm(5.0, 2);
	aa.NewTerm(6.0, 1);
	aa.NewTerm(7.0, 0);

	bb.NewTerm(7.0, 8);
	bb.NewTerm(5.0, 2);
	bb.NewTerm(9.0, 0);

	cc = aa - bb;
	dd = aa * bb;
	cout << "aa - bb: " << cc;
	cout << "aa * bb: " << dd;

	system("pause");
}
