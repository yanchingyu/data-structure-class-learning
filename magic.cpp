#include <iostream>
using namespace std;

void magic(const int n)
{
	//���ͤ@�Ӥj�p��n���]�N��}�A�䤤n���_��
	const int magicMax = 51;				// �̤j��}�j�p
	int magic[magicMax][magicMax] = {0};

	// �T�wn�����T��
	if (n > magicMax || n < 1)
	{
		cout << "Error! n out of range \n";
		return;
	}
	else if (!(n % 2))
	{
		cout << "Error! n isn't odd \n";
		return;
	}
		
	int num = 2, i = 0, j = (n - 1) / 2;			// i �� j �O�ثe����m
	magic[0][(n - 1) / 2] = 1;				// �Ĥ@�C��������m

	while (num <= n * n)					
	{
		//// �V���W����
		if (i - 1 < 0 && !(i == 0 && j == 0))	i = n - 1;
		else	i = i - 1;

		if (j - 1 < 0 && !(i == -1 && j == 0))	j = n - 1;
		else	j = j - 1;

		if ((i < 0 && j < 0) || magic[i][j])			// magic[i][j]�w�g�Q�񺡡A���U���� && ��i�Mj��0�ɪ��P�_
		{
			i += 2;
			j += 1;
		}
		
		magic[i][j] = num;
		num++;
	}

	for (int a = 0; a < n; a++)
	{
		for (int b = 0; b < n; b++)
		{
			cout << magic[a][b] << "\t";
		}
		cout << endl;
	}
}

int main()
{
	int n;						//n�n�_��
	while (cin >> n)
	{
		magic(n);
	}

	system("pause");
	return 0;
}