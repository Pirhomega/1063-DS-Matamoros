/*
ProgramName:	Program-3
Author:			Corbin Matamoros
Description:
	This program will read in a bunch of animals names from an input file into
	a doubly-linked list. It will then prompt the user to input a random
	value, "m," between 1 and 13 (inclusive) and another random value between 1 
	and RANDMAX. It will afterwards read in a value from the input file again, 
	find the length of that value, multiply it by "m" and move that product's 
	number of spaces within the linked list. It will move to the right if the 
	product is even and to the left otherwise. The animal whose node the 
	product landed on will be deleted and the list will get smaller. Output 
	will show only the 11th dispatched animal, however. 
Course:			1063 Data Structures & ADT
Semester:		Spring 2018
Data:			04 27 2018
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*Struct contains the info each Node will hold, specifically pointers to the
previous and next Nodes, and a string to hold the animal name.*/
struct Node
{
	string animal;
	Node* next;
	Node* prev;
	Node(string x)
	{
		animal = x;
		next = NULL;
		prev = NULL;
	}
};

class killAnimals
{
private:
	Node* Current;
	Node* Head;
public:
		
	killAnimals()
	{
		Current = Head = NULL;
	}

	/*	FunctionName:	killAnimals
		Description:	Initializes the Current pointer to the head of the list
		Params:			None
		Returns:		void
	*/
	void moveToHead()
	{
		Current = Head;
	}

	/*	FunctionName:	fillList
		Description:	Fills the list with all that is read in from the input
						file animals.txt.
		Params:			inputAnimal - animal to be added to list
		Returns:		void
	*/
	void fillList(string inputAnimal)
	{
		Node* temp = new Node(inputAnimal);

		//If the list is empty, set the first Node as Head and Current
		if (!Current)
		{
			Current = temp;
			Head = temp;
		}

		//if the list has >0 Nodes, add on to it and update pointers
		else
		{
			Current->next = temp;
			temp->prev = Current; //links temp to list
			temp->next = Head; //link rear of list to front (Head)
			Head->prev = temp; //links front of list to rear
			Current = temp;
		}
	}

	/*	FunctionName:	theChopper
		Description:	Traverses the list, and whatever Node it falls on, it 
						deletes
		Params:			multiplier - value determined by program user
						size - length of animal name
						outfile - used to print to an output file
						deaths - used to print out every 11th kill
		Returns:		void
	*/
	void theChopper(int multiplier, int size, ofstream &outfile, int deaths)
	{
		int spaces = multiplier * size; //number of spaces to traverse list
		Node* temp; //used to delete (kill) a Node (animal)
		Node* left; //points to Node to left of Current
		Node* right; //point to Node to right of Current

		if (spaces % 2 == 0) //if even, traverse list going towards the rear
		{
			for (int i = 0; i < spaces; i++)
			{
				Current = Current->next;
			}
		}
		else //if odd, traverse list going towards the front
		{
			for (int i = 0; i < spaces; i++)
			{
				Current = Current->prev;
			}
		}
		temp = Current;
		left = Current->prev;
		right = Current->next;
		left->next = right;
		right->prev = left;
		Current = right;
		if (deaths % 11 == 0 && deaths != 0) //print to file every 11th kill
			outfile << "- " << temp->animal << '\n';
		delete temp;
	}

	/*	FunctionName:	theWinner
		Description:	Creates a variable for the surviving animal and sends it
						back to main
		Params:			none
		Returns:		string
	*/
	string theWinner()
	{
		string x;
		x = Current->animal;
		return x;
	}
};

int main()
{
	killAnimals K;
	int m, deathCount = 0, counter = 0;
	string inputAnimal, lastAnimal;
	ifstream infile;
	ofstream outfile;
	infile.open("animals.txt");
	outfile.open("eliminated.txt");

	outfile << "ProgramName:	Program-3\n"
		<< "Author:			Corbin Matamoros\n"
		<< "Description:	\n	This program will read in a bunch of animals "
		<< "names\n"
		<< "from an input file into a doubly - linked list. It will then\n"
		<< "prompt the user to input a random value, \"m\" between 1 and 13\n"
		<< "(inclusive) and another random value between 1"
		<< "and RANDMAX. \nIt will afterwards read in a value from the input "
		<< "file\n"
		<< "again, find the length of that value, multiply it by \"m\" and\n"
		<< "move that product's number of spaces within the linked list.\n"
		<< "It will move to the right if the product is even and to the left\n"
		<< "otherwise. The animal whose node the product landed on will be\n"
		<< "deleted and the list will get smaller. Output will show only the\n"
		<< "11th dispatched animal, however.\n"
		<< "Course:			1063 Data Structures & ADT\n"
		<< "Semester:		Spring 2018\n"
		<< "Date:			04 27 2018\n\n"
		<< "First: ";
	while (infile >> inputAnimal) //reads in animals from input file
	{
		K.fillList(inputAnimal);
		counter++; //keeps track of number of animals added to list
	}

	cout << "Enter a number between 0 and 14 (it can't be 0 or 14)! >> ";
	cin >> m; /*asks user for a random number to calculate spaces to traverse
			  in the theChopper function*/
	while (m < 1 || m > 13) //if user inputs a number below 1 or above 14
	{
		cout << '\n' << "Invalid input. Please try again >> ";
		cin >> m;
	}

	K.moveToHead(); //initializes Current to the front of the list

	infile.clear(); //clears the eof
	infile.seekg(0, ios::beg); /*restarts the infile reading so as to begin 
							   reading in from the beginning of the input 
							   file*/
	while (deathCount < counter - 1) //loops until one animal remains
	{
		infile >> inputAnimal;
		K.theChopper(m, inputAnimal.length(), outfile, deathCount);
		deathCount++;
	}

	lastAnimal = K.theWinner(); //retreives name of remaining animal
	outfile << "WINNER: " << lastAnimal << " !!";
	return 0;
}
