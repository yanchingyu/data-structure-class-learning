#include <iostream>
#include <string>
using namespace std;

class array_link_list
{
private:
	string data[100];
	int link[100];
	int first;
public:
	array_link_list();

	void build_original_list();
	void print();
	void insert_Gat(int x, int new_node);
};

array_link_list::array_link_list()
{
	first = 5;
}

void array_link_list::build_original_list()
{
	data[2] = "fat "; link[2] = 4;
	data[3] = "cat "; link[3] = 6;
	data[4] = "hat "; link[4] = -1;
	data[5] = "bat "; link[5] = 3;
	data[6] = "eat "; link[6] = 2;
	data[8] = "gat "; 
}

void array_link_list::print()
{
	int temp = first;
	while (link[temp] != -1)
	{
		cout << data[temp] << "->";

		temp = link[temp];
	}
	cout << data[temp] << "->" << endl;
}

void array_link_list::insert_Gat(int x, int new_node)
{
	link[new_node] = link[x];
	link[x] = new_node;
}

int main()
{
	array_link_list a;
	
	a.build_original_list();
	a.print();

	int x = 2, new_node = 8;
	a.insert_Gat(x, new_node);
	a.print();

	system("pause");
}


