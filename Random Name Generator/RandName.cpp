#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;
struct nameGenerator
{
	int number;
	char letter;

	nameGenerator()
	{
		number = 0;
		letter = ' ';
	}
};
int main()
{
	int userNum, i, j, k, size;

	ifstream infile;
	ofstream outfile;
	infile.open("Letters.txt");
	outfile.open("Output.txt");

	srand(time(0));
	char nameArray[100], favVow;
	nameGenerator pickNum[100];
	for (i = 0; i < 100; i++)
	{
		pickNum[i].number = rand() % 100;
		infile >> pickNum[i].letter;
		cout << pickNum[i].letter << " " << pickNum[i].number << " ";
	}
	cout << "How long do you want your name to be?\n";
	cin >> size;
	cout << "What is your favorite vowel?\n";
	cin >> favVow;
	j = 0;
	k = 0;
	while (j < size)
	{
		cout << "Pick an integer between 1 and 100!\n";
		cin >> i;
			while (k < 100)
			{
				if (i == pickNum[k].number || i == pickNum[k].number / 2 || i == pickNum[k].number / 3 || i == pickNum[k].number / 5)
				{
					nameArray[j] = pickNum[k].letter;
					k = 101;
					cout << nameArray[j];
				}
				else
					k++;
			}
			if (k == 100)
				nameArray[j] = 'a';
			if (j == 1 || j == 3 || j == 6 || j == 9 || j == 12)
			{
				nameArray[j] = favVow;
				k = 0;
				cout << '\n';
			}
			if (j%5 == 0 && j != 0)
				nameArray[j] = '-';
		cout << '\n';
		k = 0;
		j++;
	}
	outfile << "Here's your name: ";
	for (i = 0; i < size; i++)
	{
		outfile << nameArray[i];
	}
	cout << '\n';
	system("pause");
	return 0;
}
