/*Matamoros, Corbin
1063 Data Structures - Griffin
3/24/2018
This program converts all lowercase letters in a word to uppercase*/

#include <string>
#include<iostream>
#include<fstream>

using namespace std;

/*	FunctionName: toUpper
	Description: Loops through each letter in a word, determines if the letter has an ASCII value for lowercase letters, and if so
		subtracts 32 resulting in the lowercase version of the letter.
	Params: string lower - string holding the word to be uppercased
	Returns: lower
*/
string toUpper(string lower)
{
	for (int i = 0; i < lower.length(); i++)
	{
		if ((int)lower[i] >= 97 && (int)lower[i] <= 122) /*ASCII values between 97 and 122 are lowercase letters of the alphabet.*/
		{
			lower[i] = lower[i] - 32; //subtracts 32 if the letter was lowercase (between 97 and 122)
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
	while (infile >> lowerWord)//reads in from an input file until the last entry has been read
	{
		upperWord = toUpper(lowerWord); //calls the toUpper function
		outfile << upperWord << '\n';
	}
	outfile.close();
	infile.close();
	return 0;
}
