#include "node.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>

/*
Code by Michael Yan
3/21/2020
This code creates a Red Black Tree, able to add, search, and print (delete later)
*/

using namespace std;


void addNode(Node** head, Node* parentNode, int number){ //insert pseudo: https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
	if(parentNode->getData() == 0){
		parentNode->setColor(1);
		parentNode->setData(number);
	}
	else{
		if(number < parentNode->getData()){
			if (parentNode->getLeft() == NULL){
				Node* newNode = new Node();
				newNode->setData(number);
				newNode->setParent(parentNode);
				parentNode->setLeft(newNode);
				//call the fixTree function
			}
			else{
				addNode(head, parentNode->getLeft(), number);
			}
		}
		else{
			if(parentNode->getRight() == NULL){
				Node* newNode = new Node();
				newNode->setData(number);
				newNode->setParent(parentNode);
				parentNode->setRight(newNode);
				//fixTree
			}
			else{
				addNode(head, parentNode->getRight(), number);
			}
		}
	}
}



void printTree(Node* parentNode, int count){
	if(parentNode->getRight() != NULL){
		print(parentNode->getRight(), count+1);
	}
	int n = count; //temporary variable
	while(count > 0){
		cout << "	";
		count--;
	}
	if(parentNode->getColor() == 1){ //black
		cout << "\033[4;35m" << parentNode->getData() << "\033[0m" << endl;
	}
	else{ //red
		cout << "\033[4;31m" << parentNode->getData() << "\033[0m" << endl;
	}
	if(parentNode->getLeft() != NULL){
		printTree(parentNode->getLeft(), n+1);
	}
}



void fixTree(Node** head, Node* newNode){ //check and fix tree after every insertion
	
	Node* parent = NULL;
	Node* grandparent = NULL;
	
	
	while(newNode->getParent() != NULL && newNode->getParent()->getColor() == 0 && newNode != *head){
		
		parent = newNode->getParent();
		grandparent = parent->getParent();//not needed
		
		if(newNode->getParent() == newNode->getParent()->getParent()->getLeft()){ //if parent is left child
			Node* uncle = newNode()->getParent()->getParent()->getRight();
			
			if(uncle != NULL && uncle->getColor() == 0){ //if uncle is red
				newNode->getParent()->setColor(1);
				uncle->setColor(1);
				newNode->getParent()->getParent()->setColor(0); //grand parent is red
				newNode = newNode->getParent()->getParent();
			}
			
			else{ //if uncle is black
				if(newNode == newNode->getParent()->getRight()){
					newNode = newNode->getParent();
					//do a left rotation
					//newNode = parent
					//parent = newNode->getParent(); //parents
				}
				//newNode is left child
				//do a right rotation
			}
		}
		
		
		
		
		else{ //if parent is right childe
			
			Node* uncle = grandparent->getLeft();
			
			//same as parent left child
			if(uncle != NULL && uncle->getColor() == 0){ //if uncle is red
				node* input = new node();
				input = newNode()->getParent()->getParent()->getLeft();
				newNode->getParent()->setColor(1);
				input->setColor(1);
				newNode->getParent()->getParent()->setColor(0);
				newNode = newNode->getParent()->getParent();
			}
			else{
				if(newNode == newNode->getParent()->getLeft()){
					newNode = newNode->getParent();
					//do a right rotation
				}
				newNode->getParent()->setColor(1);
				newNode->getParent()->getParent()->setColor(0);
				//left rotation, but with the parent of parent of newNode
			}
		}
		
	}
	*head->setColor(2);
}




void rotateTree(Node** head, Node* nextNode, int leftright){
	
	//0 is left, 1 is right
	if(leftright = 0){ //left rotation
		//set current to nextNode right
		//set nextNode right to current's left
		// if current left is not null, 
			//set current left's parent to nextNode
		//set current's parent to nextNode's parent
		// if nextNode is the head of tree,
			//set head to current
		// else	
			//if nextNode is a left child, set to current node
			//else set nextNode's parent's right child to current node
		//set current's left to nextNode
		//set nextNode parent to current
	}
	if(leftright = 1){ //right rotation
		//same, but left and rights are swapped
	}
}







bool searchTree(Node* ){
	//not now
}



Node* deleteNode(Node* head, int number){
	//later
}


int main(){
	
	int index = 0;
	int *stor = new int[1000];
	
	
	Node* head = new Node(); //root
	
	
	while(true){ //give user action command options
		cout << "\nEnter a command. Type 'add', 'read', 'print', or 'quit': ";
		
		char* command = new char[10];
		cin.getline(command, 10);
		int number = 0;
		
		if(strcmp(command, "add") == 0){ //add numbers in console
			cout << "Enter the number you want to add: " <<endl;
			cin >> number;
			cin.get();
			addNode(&head, head, number);
		}
		
		else if(strcmp(command, "read") == 0){
			cout << "Type the file name (include the .txt extension): ";
			char* filename = new char[100];
			cin.getline(filename, 100);
			
			ifstream inFile; //get file input
			inFile.open(filename);
			
			int n = 0;
			while(inFile >> n){
			
				stor[index] = n; //fill stor with file
				index++;
			}
			
			//fill array?
			for(int i = 0; i < index; i++){
				//if(stor[i] == ')
				//addNode(head, stor[i]);
			}
		}
		
		else if(strcmp(command, "print") == 0){ //print rbt
		}
		
		else if(strcmp(command, "quit") == 0){ //if user wants to quit program
			return false; //quit program
		}
	
	}	

}
