Here's the C++ solution to the Moby Dick word counter problem posed in class. Solved it without functions, and it has comments. Sorry.

Corbin Matamoros
1/23/2018
CMPS 1063 - Griffin
This program reads through an input file containing preprocessed text. It then counts each unique word and how many times it was used.
Lastly it finds which word was used the most and how many times it was used.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*create a struct to later create an array that holds the words
used in the text file and the number of times any word was used*/
struct wordNode
{
	string Word;
	int wordCount;
};

int main()
{
	ifstream infile;
	ofstream outfile;
	infile.open("Text.txt");
	outfile.open("Output.txt");

	wordNode wordArray[10000];
	int i, count = 0, j, freqCount = 1;
	string newWord, freqWord;

	/*initialize the struct array with blank spaces for the string portion
	and zeros for the integer portion*/
	for (i = 0; i < 10000; i++) 
	{
		wordArray[i].Word = " ";
		wordArray[i].wordCount = 0;
	}
	 /*filling the first index location of the struct array. This eliminates
	 one repetition from the following while loop*/
	infile >> wordArray[0].Word;
	wordArray[0].wordCount = 1;

	i = 1;
	j = 0;
	
	/*outer loop reads in every word from the input file. Once it detects
	there is nothing left to read in, the while loop will stop*/
	while (infile >> newWord)
	{
		/*second loop is used to loop through all previous indeces to check for
		the same word as read in to string newWord. integer j must be positive*/
		while (j < i && j >= 0)
		{
			/*if statement checks for identical words to string newWord. If it 
			finds one, that word's word count in the struct array is 
			incremented by one, and the integer j is flagged (made negative)*/
			if (newWord == wordArray[j].Word)
			{
				wordArray[j].wordCount++;
				j = -2;
			}
			j++;
		}
		/*if statement checks for positive j values. If j is negative, set by
		previous if statement, that means the newly read in word was found 
		in the struct array. If j is positive, the newly read in word has never
		been read in before, so the next index in the struct array is set to 
		that new word and its count is incremented by one.*/
		if (j > 0)
		{
			wordArray[i].Word = newWord;
			wordArray[i].wordCount++;
			i++;
		}
		/*i only increments if a new word was read in. If no new word was read
		in, then we will keep the index (i) the same to eliminate spaces in
		the output file. Makes things cleaner.*/
		j = 0;
	}
	for (j = 0; j < i; j++)
	{
		outfile << wordArray[j].Word << " " << wordArray[j].wordCount << '\n';

		/*find the most frequently used word and how many times it was used*/
		if (wordArray[j].wordCount > freqCount)
		{
			freqCount = wordArray[j].wordCount;
			freqWord = wordArray[j].Word;
		}	
	} 
	outfile << "The most used word is '" << freqWord << "' with " << freqCount << " uses!";
	infile.close();
	outfile.close();
	return 0;
}
