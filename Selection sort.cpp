#include <iostream>
#include <ctime>
using namespace std;

#define size 100

void swap(int list[], int P1, int P2)
{
	int temp = list[P1];
	list[P1] = list[P2];
	list[P2] = temp;
}

void selectionSort(int list[])
{
	for (int i = 0; i < size; i++)
	{
		int IP = i;
		for (int j = i + 1; j < size; j++)
			if (list[j] < list[IP])
			{
				IP = j;
			}
			
		swap(list, i, IP);
	}
}

int main()
{
	srand(time(0));
	int list[size];

	for (int i = 0; i < size; i++)
	{
		list[i] = rand() % 1000;
	}

	selectionSort(list);

	for(int i=0;i<size;i++)
		cout << list[i] << " ";

	system("pause");
	return 0;
}