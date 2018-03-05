#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Node
{
	string word;
	Node* next;
	Node()
	{
		word = " ";
		next = NULL;
	}
	Node(string w)
	{
		word = w;
		next = NULL;
	}
};

class linkedList
{
private:
	Node* Top;
	Node* Rear;
	int listSize = 0;
public:
	linkedList()
	{
		Top = NULL;
		Rear = NULL;
	}
	void listPush(string pushWord)
	{
		Node* temp = new Node(pushWord);
		if (Top == NULL)
		{
			Top = temp;
		}
		else
		{
			temp->next = Top;
			Top = temp;
		}
	}
	string listPop()
	{
		if (Top == NULL)
		{
			cout << "List is empty!\n";
		}
		string popWord;
		Node* temp = Top;
		popWord = Top->word;
		Top = Top->next;
		delete temp;
		return popWord;
	}
};

int main() 
{
	linkedList pushPop;
	string ppWord = " ";
	int listSize = 0, i = 0;

	ifstream infile;
	infile.open("animals.txt");
	while (infile >> ppWord)
	{
		pushPop.listPush(ppWord);
		listSize++;
	}
	for (i = listSize; i > 0; i--)
	{
		cout << pushPop.listPop() << '\n';
	}
	system("pause");
	return 0;
}
