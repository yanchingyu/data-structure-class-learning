#include <iostream>
using namespace std;

#define size 4

template<class X>
void swap(X *a, X *b)
{
	X temp = *a;
	*a = *b;
	*b = temp;
}

template<class T>
void permutation(T perm[], const int k, const int m)			// 產生a[k], …, a[m] 的所有排列
{
	if (k == m)		//輸出排列
	{
		for (int i = 0; i <= m; i++)
			cout << T(perm[i]) << "\t";
		cout << endl;
	}
	else
	{		// a [k : m] 還有超過一種以上的排列，遞迴產生它們
		for (int i = k; i <= m; i++)
		{
			swap(&perm[k], &perm[i]);
			permutation(perm, k + 1, m);
			swap(&perm[k], &perm[i]);
		}

	}
}

int main()
{
	int perm[size] = {1,2,3,4};
	permutation(perm, 0, size - 1);
	cout << endl;

	char perm1[size] = { 'A','B','C','D' };
	permutation(perm1, 0, size - 1);

	system("pause");
	return 0;
}