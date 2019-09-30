#include <iostream>
using namespace std;

void magic(const int n)
{
	//產生一個大小為n的魔術方陣，其中n為奇數
	const int magicMax = 51;				// 最大方陣大小
	int magic[magicMax][magicMax] = {0};

	// 確定n的正確性
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
		
	int num = 2, i = 0, j = (n - 1) / 2;			// i 跟 j 是目前的位置
	magic[0][(n - 1) / 2] = 1;				// 第一列的中間位置

	while (num <= n * n)					
	{
		//// 向左上移動
		if (i - 1 < 0 && !(i == 0 && j == 0))	i = n - 1;
		else	i = i - 1;

		if (j - 1 < 0 && !(i == -1 && j == 0))	j = n - 1;
		else	j = j - 1;

		if ((i < 0 && j < 0) || magic[i][j])			// magic[i][j]已經被填滿，往下移動 && 當i和j為0時的判斷
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
	int n;						//n要奇數
	while (cin >> n)
	{
		magic(n);
	}

	system("pause");
	return 0;
}