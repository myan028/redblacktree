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


void addNode(Node** root, Node* parentNode, int number){ //insert pseudo: https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
	if (parentNode->getData() == 0){
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
				addNode(root, parentNode->getLeft(), number);
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
				addNode(root, parentNode->getRight(), number);
			}
		}
	}
}



void printTree(Node* ){
	
}



bool searchTree(Node* ){
	//wip
}



//Node* deleteNode(Node* head, int number){}


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
