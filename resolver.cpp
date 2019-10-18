#include <iostream>
#include <vector>

using namespace std;

void print_vec(vector<int> &v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << ",";
	}
	cout << "\n";
}

int main()
{
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 20; j++)
		{
			if (j == 4)
				break;
			cout << "Hello there : " << i << "," << j << "\n";
		}
	}
}
