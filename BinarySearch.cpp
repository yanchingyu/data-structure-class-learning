#include <iostream>
using namespace std;

#define size 10

void selectionSort(int data[])
{
	for (int i = 0; i < size; i++)
	{
		int k = i;

		//т程计k
		for (int j = i + 1; j < size; j++)
		{
			if (data[j] < data[k])
				k = j;
		}

		// swap 盢程计籔材iが传
		int temp = data[i];
		data[i] = data[k];
		data[k] = temp;
	}
}

int binarySearch(int data[], int num)
{
	int right = size - 1, left = 0;

	while (left <= right)
	{
		int middle = (right + left) / 2;
		if (data[middle] > num)
			right = middle - 1;
		else if (data[middle] < num)
			left = middle + 1;
		else
			return middle;
	}
	return -1;
}

int main()
{
	int data[size] = { 9,7,5,0,1,3,4,8,2,6 };
	int num;

	selectionSort(data);
	while (cin >> num)
	{
		cout << binarySearch(data, num) << endl;
	}

	system("pause");
	return 0;
}