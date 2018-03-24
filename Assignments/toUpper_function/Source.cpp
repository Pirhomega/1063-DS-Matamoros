/*Matamoros, Corbin
1063 Data Structures - Griffin
3/24/2018
This program converts all lowercase letters in a word to uppercase*/

#include <string>
#include<iostream>
#include<fstream>

using namespace std;

string toUpper(string lower)
{
	for (int i = 0; i < lower.length(); i++)
	{
		if ((int)lower[i] >= 97 && (int)lower[i] <= 122)
		{
			lower[i] = lower[i] - 32;
		}
	}
	return lower;
}

int main()
{
	string upperWord = " ", lowerWord = " ";
	ifstream infile;
	ofstream outfile;
	infile.open("Input.txt");
	outfile.open("Output.txt");
	cout << lowerWord << '\n';
	while (infile >> lowerWord)
	{
		upperWord = toUpper(lowerWord);
		outfile << upperWord << '\n';
	}
	outfile.close();
	infile.close();
	return 0;
}
