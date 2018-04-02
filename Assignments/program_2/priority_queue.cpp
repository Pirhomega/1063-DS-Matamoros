/*
Author:		Matamoros, Corbin
Due Date:	4/2/2018
Class:		Data Structures & ADT - Griffin
Program:	Priority Queue
Description: 
			This program will create a list-based queue of animal names to be
read in from an input file. It will assign a priority level to each name - 
larger words receive a lower piority than smaller ones - and place smaller 
words towards the front of the queue. Words of the small length will be ordered
alphabetically
Disclaimer:	I wanted to learn to re-create the program 2 assignment from 
			scratch, and therefore this program will not be identical to the
			one I was told to copy and use. Also, as of the due date, this
			program does not work for the assignment input file. It works for 
			smaller inputs, though.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Struct: each item in the queue list will hold the word, its length, and a pointer
//to the next item in the list
struct Node
{
	string word;
	Node* next;
	int wordSize;

	Node()
	{
		word = " ";
		next = NULL;
		wordSize = 0;
	}
	Node(string w, int s)
	{
		word = w;
		next = NULL;
		wordSize = s;
	}
};

/*Class:	Queue - Contains methods to add, subtract, and print off values
					from the list-based queue
*/
class Queue
{
private: 
	Node* Front; //points to the smallest word in the list
	Node* Rear; //points to the largest word in the list
	Node* Traverser; //used to traverse the list (see push function comments)
	Node* Referencer; //pointer that stays one behind the traverser
public:
	Queue()
	{
		Front = Rear = Traverser = Referencer = NULL;
	}
	
	/*	FunctionName: push
		Description:
			Adds words to the list-based queue and orders them smallest to 
			largest, starting at the front with the smallest and ending at the
			rear with the largest
		Params:
			string word - word to be added to the list
			int size - the number of letters in the word
		Returns: void
	*/
	void push(string word, int size)
	{
		//when the list is completely empty, this runs
		Node* temp = new Node(word, size);
		if (Front == NULL)
		{
			Front = temp;
			Rear = temp;
			Traverser = Front;
			Referencer = Traverser;
		}
		else
		{
			/*runs if the new word is smaller than the smallest word 
			in the list*/
			if (temp->wordSize <= Front->wordSize)								   
			{
				temp->next = Front;
				Front = temp;
				Traverser = Front;
			}
			
			/*runs if the new word is larger than the largest word 
			in the list*/
			else if (temp->wordSize >= Rear->wordSize)
			{
				Rear->next = temp;
				Rear = temp;
			}
			
			/*runs if the new word is neither smaller nor larger than the 
			smallest and largest word*/
			else
			{
				/*traverses through the list until it finds words of
				comparable size. If it doesn't find any, it sets a new area
				for that specific size*/
				Traverser = Traverser->next;
				
				/*compares temp's size to the size of the word the traverser
				is pointing to. Once the traverser finds a value greater than
				temp's, it used the referencer pointer (which is one item
				behind the traverser pointer) to add temp to the list, in
				between traverser and referencer pointers*/
				while (temp->wordSize > Traverser->wordSize)
				{
					Referencer = Traverser;
					Traverser = Traverser->next;
				}
				temp->next = Traverser;
				Referencer->next = temp;
				Traverser = Front;
				Referencer = Traverser;
			}
		}
	}

	/*	FunctionName: pop
		Description:
			removes the word at the front of the list, i.e. the smallest word
			in the list at that time
		Params:
			none
		Returns: 
			string
	*/
	string pop()
	{
		Node* temp = Front;
		string popWord = " ";

		/*if Front is NULL, then there is no word to pop off the list. Return
		an error message and a space so that the program continues to read
		in the next item from the input file*/
		if (Front == NULL)
		{
			cout << "error: cannot pop off empty queue." << '\n';
			return "FAILURE";
		}

		//initiates for cases when there are more than 2 items in the queue
		else if (Front != Rear)
		{
			popWord = Front->word;
			Front = Front->next;
			Traverser = Front;
			Referencer = Traverser;
			delete temp;
			return popWord;
		}

		/*special case when there is only one value in the queue. If that last
		word is popped off, the Front pointer is set to NULL. If another pop
		command is run, the NULL sets up the first if statement to run (above)
		*/
		else if (Front == Rear)
		{
			popWord = Front->word;
			Front = Rear = Traverser = Referencer = NULL;
			return popWord;
		}
	}

	/*	FunctionName: print
		Description:
			Will print off whatever words are in the queue at any time. It 
			does this by using the traverser pointer to travel through the list
			and cout the word to which it points
		Params:
			none
		Returns: 
			void
	*/
	void print()
	{
		int i = 1;
		Traverser = Front;
		if (Front == NULL)
		{
			cout << "Queue is empty.\n";
			return;
		}
		while (Traverser != Rear)
		{
			cout << i << " " << Traverser->word << '\n';
			Traverser = Traverser->next;
			i++;
		}
		cout << i << " " << Traverser->word << '\n';
	}
};
int main()
{
	ifstream infile;
	ofstream outfile;
	infile.open("Input.txt");
	outfile.open("Output.txt");
	Queue Q;
	string inputCommand = " ", inputWord = " ", animal = " ";
	int i = 1;
	outfile << "Animals Popped Off the Queue" << '\n' << '\n';
	
	/*an eof type of while loop, this one will continue to read in until
	it has reached the last entry in the input file*/
	while (infile >> inputCommand)
	{
		/*if the while loop read in push, the program will read in the word
		to push into the list-based queue*/
		if (inputCommand == "push")
		{
			infile >> inputWord;
			Q.push(inputWord, inputWord.length());
		}

		/*if the while loop read in pop as an input command, the program will
		call the pop function above and print it to an output file*/
		else
		{
			animal = Q.pop();
			outfile << i << " " << animal << '\n';
			i++;
		}
	}
	outfile << '\n' << "Animals Remaining on the Queue (in order of priority)"
		<< '\n' << '\n';

	/*after popping off all value commanded by the input file, the program will
	print off whatever words are still within the list-based queue.*/
	Q.print();
	return 0;
}
