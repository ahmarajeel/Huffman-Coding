#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class ListBinNode
{
	public: 
	int prob;
	string chaStr;
	ListBinNode* next;
	ListBinNode* left;
	ListBinNode* right;
	 
	ListBinNode()
	{
		next = NULL;
		left = NULL;
		right = NULL;
	}
	
	ListBinNode(int item)
	{
		prob = item;
		next = NULL;
		left = NULL;
		right = NULL;
	}
	
	ListBinNode(int item, string str)
	{
		chaStr = str;
		prob = item;
		next = NULL;
		left = NULL;
		right = NULL;
		
	}
	
	~ListBinNode() 
	{
		delete next;
		delete left;
		delete right;
	}
	
	void printNode(ListBinNode* T, ofstream &outFile3)
	{
		outFile3 << T->chaStr << " " << T->prob << " ";
		if(T->next == NULL)
			outFile3 << "NULL";
		else
			outFile3 << T->next->chaStr;
		if(T->left == NULL)
			outFile3 << " NULL";
		else
			outFile3 << " " << T->left->chaStr;
		if(T->right == NULL)
			outFile3 << " NULL";
		else
			outFile3 << " " << T->right->chaStr;	
			
			
		outFile3 << endl;
	}
};

class HuffmanLinkedList
{
	public: 
	ListBinNode* listHead;
	ListBinNode* oldListHead;
	HuffmanLinkedList()
	{
		listHead = new ListBinNode(-9999, "dummy");
		oldListHead = new ListBinNode(-9999, "dummy");
		oldListHead->next = listHead->next;
	}
	
	ListBinNode* findSpot(int item)
	{
		ListBinNode* spot = listHead;
		while(spot->next != NULL && spot->next->prob < item)
		{
			spot = spot->next;
		}
		return spot;
	}
	
	void listInsert(ListBinNode* node)
	{
		ListBinNode* spot;	
		spot = findSpot(node->prob);
		node->next = spot->next;
		spot->next = node;
	}
	
	void printList(int data, ofstream &outFile)
	{
			outFile << "Inserting " << data << ": ";
			outFile << "listHead->" << "\"(dummy,0,";
			ListBinNode* current;
			current = listHead;
			while(current->next != NULL)
			{
				outFile << current->next->chaStr <<")->(" << current->next->chaStr << "," << current->next->prob << ",";
				current = current->next;
			}
			outFile << "NULL)->NULL";
			outFile << endl;
	}
	
	bool isEmpty()
	{
		if(listHead->next == NULL)
			return true; 
		else
			return false;
	}
};

class HuffmanBinaryTree
{
	public:
	string chaStr;
	int prob;
	string code;
	ListBinNode* root;
	HuffmanBinaryTree(ListBinNode* rootNode)
	{
		root = rootNode;
	}	
	
	//recursive
	void constructCharCode(ListBinNode* T, string code, ofstream &outFile1)
	{
		if(T == NULL)
			return;
		else if(T->left == NULL && T->right == NULL)
		{
			outFile1 << T->chaStr << " " << code << endl;
		}
		else
			constructCharCode(T->left, code + "0", outFile1);
			constructCharCode(T->right, code + "1", outFile1);
				
	}
	
	void preOrder(ListBinNode* T, ofstream &outFile2)
	{
		if(T == NULL)
		return;
		else
		{
			ListBinNode *temp = new ListBinNode();
			temp->printNode(T, outFile2);
			preOrder(T->left, outFile2);
			preOrder(T->right, outFile2);
		}	
	}
};

int main(int argc, char* argv[])
{
	
	//step 2:
		
	ifstream myFile;
	ofstream outFile1(argv[2]);
	ofstream outFile2(argv[3]);
	ofstream outFile3(argv[4]);
	myFile.open(argv[1]);
	int probability;
	string chaString;
	HuffmanLinkedList myList;
	
	while (myFile >> chaString >> probability)
	{
		ListBinNode* newNode = new ListBinNode(probability, chaString);
		myList.listInsert(newNode);
	}

	myFile.close();

	ListBinNode* Root = new ListBinNode();
	while(myList.listHead->next->next != NULL)
	{
		ListBinNode* newNode = new ListBinNode();
		newNode->prob = myList.listHead->next->prob + myList.listHead->next->next->prob;
		newNode->chaStr = myList.listHead->next->chaStr + myList.listHead->next->next->chaStr;
		newNode->left = myList.listHead->next;
		newNode->right = myList.listHead->next->next;
		myList.listHead->next = myList.listHead->next->next->next;
		myList.listHead->printNode(newNode, outFile3);
		myList.listInsert(newNode);
		myList.printList(newNode->prob, outFile3);
		Root = newNode;
	}
	HuffmanBinaryTree* myTree = new HuffmanBinaryTree(Root);
	myTree->constructCharCode(Root, "", outFile1);
	myTree->preOrder(Root, outFile2);
	outFile1.close();
	outFile2.close();
	outFile3.close();
	return 0;
	
}
