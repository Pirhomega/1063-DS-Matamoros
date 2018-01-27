#include <iostream>
using namespace std;

int main()
{
	int i = 0, j = 0, k = 0, Nums[15][15];

	for(i = 0; i < 15; i++) 
	{
		for(j = 0; j < 15; j++) 
		{
			Nums[i][j] = k;
			k++;
		}
	}
	for(i = 0; i < 15; i++)
	{
		for(j = 0; j < 15; j++)
		{
			cout << Nums[j][i] << " ";
		}
		cout << '\n';
	}
	return 0;
}