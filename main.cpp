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

void addNode(Node*, Node*, int);
void printTree(Node*, int);
void fixTree(Node*, Node*);
void rotateTree(Node*, Node*, int);


using namespace std;


Node* head = new Node; //root


void addNode(Node* head, Node* parent, int input){ //insert pseudo: https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
	if(head->getData() == NULL){
		//cout << "yuh";
		//head = parent;
		parent->setColor(1);
		parent->setData(input);
	}
	else{
		if(input < parent->getData()){ //if the input is less than previous
			if(parent->getLeft() == NULL){ //if no left child
				Node* tempNode = new Node();
				tempNode->setData(input);
				tempNode->setParent(parent);
				parent->setLeft(tempNode);
				cout << "fixtree input less than parent. ";
				fixTree(head, tempNode); //rotate
			}
			else{
				addNode(head, parent->getLeft(), input); //call recursively to the left until no left child
			}
		}
		else{ //if the input is greater than or equal to the previous
			cout << "here. ";
			if(parent->getRight() == NULL){ //if no right child
				Node* tempNode = new Node();
				tempNode->setData(input);
				tempNode->setParent(parent);
				parent->setRight(tempNode);
				cout << "fixtree input greater or equal to parent. ";
				fixTree(head, tempNode); //rotate
			}
			else{
				addNode(head, parent->getRight(), input); //call recursively to the right until no right child
			}
		}
	}
}



void printTree(Node* parent, int space){ //sideways tree print algorithm (same as bst)
	
	if(head == NULL){ //dont print an empty tree
		cout << "(tree is empty)" << endl;
		return;
	}
	
	if(parent->getRight() != NULL){
		printTree(parent->getRight(), space+1);
	}
	
	int n = space; //count variable
	
	
	while(space > 0){ //print spaces
		cout << "	";
		space--;
	}
	
	
	if(parent->getColor() == 0){ //red
		cout << "\033[1;31m" << parent->getData() << "\033[0m" << endl; //print red
	}
	else if(parent->getColor() == 1){ //black
		cout << "\033[1;34m" << parent->getData() << "\033[0m" << endl; //print black (more like blue)
	}
	
	if(parent->getLeft() != NULL){
		printTree(parent->getLeft(), n+1);
	}
	
}



void fixTree(Node* head, Node* current){ //check and fix tree after every insertion
	
	//Node* parent = NULL;
	//Node* grandparent = NULL;
	Node* parent = current->getParent(); //declare parent
	Node* grandparent = parent->getParent(); //declare grandparent
	
	//if current is the root, do nothing
	while(current != head && parent != NULL && parent->getColor() == 0){
		
		//Node* parent = current->getParent(); //declare parent
		//Node* grandparent = parent->getParent(); //declare grandparent
		
		if(parent == grandparent->getLeft()){ //if parent is left child
			Node* uncle = grandparent->getRight();
			
			if(uncle != NULL && uncle->getColor() == 0){ //if uncle is red
				parent->setColor(1);
				uncle->setColor(1);
				grandparent->setColor(0); //grand parent is red
				current = grandparent;
			}
			
			else{ //if uncle is black
				if(current == parent->getRight()){
					current = parent;
					rotateTree(head, current, 0);
					//current = parent
					//parent = current->getParent(); //parents
				}
				parent->setColor(1);
				grandparent->setColor(0);
				rotateTree(head, grandparent, 1);
			}
		}
		
		else{ //if parent is right childe
			
			Node* uncle = grandparent->getLeft();
			
			//same as parent left child
			if(uncle != NULL && uncle->getColor() == 0){ //if uncle is red
				Node* input = new Node();
				input = current->getParent()->getParent()->getLeft();
				current->getParent()->setColor(1);
				input->setColor(1);
				current->getParent()->getParent()->setColor(0);
				current = current->getParent()->getParent();
			}
			else{
				if(current == parent->getLeft()){
					current = parent;
					rotateTree(head, current, 1);
				}
				parent->setColor(1);
				grandparent->setColor(0);
				rotateTree(head, grandparent, 0);
			}
		}
		
	}
}







void rotateTree(Node* head, Node* nextNode, int leftright){
	
	//0 is left, 1 is right
	if(leftright = 0){ //left rotation
		Node* current = nextNode->getRight();
		nextNode->setRight(current->getLeft());
		if(current->getLeft() != NULL){
			current->getLeft()->setParent(nextNode);
		}
		current->setParent(nextNode->getParent());
		if(nextNode == head){
			head = current;
		}
		else{
			if(nextNode == nextNode->getParent()->getLeft()){
				nextNode->getParent()->setLeft(current);
			}
			else{
				nextNode->getParent()->setRight(current);
			}
		}
		current->setLeft(nextNode);
		nextNode->setParent(current);
	}
	if(leftright = 1){ //right rotation
		Node* current = nextNode->getLeft();
		nextNode->setLeft(current->getRight());
		if(current->getRight() != NULL){
			current->getRight()->setParent(nextNode);
		}
		current->setParent(nextNode->getParent());
		if(nextNode == head){
			head = current;
		}
		else{
			if(nextNode == nextNode->getParent()->getLeft()){
				nextNode->getParent()->setLeft(current);
			}
			else{
				nextNode->getParent()->setRight(current);
			}
		}
		current->setRight(nextNode);
		nextNode->setParent(current);
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
	
	
	//Node* head = new Node(); //root
	
	
	while(true){ //give user action command options
		cout << "\nEnter a command. Type 'add', 'read', 'print', or 'quit': ";
		
		char* command = new char[10];
		cin.getline(command, 10);
		int number = 0;	
		
		if(strcmp(command, "add") == 0){ //add numbers in console
			cout << "Enter the number you want to add: " << endl;
			cin >> number;
			cin.get();
			addNode(head, head, number);
		}
		
		/*else if(strcmp(command, "read") == 0){
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
		}*/
		
		else if(strcmp(command, "print") == 0){ //print rbt
			printTree(head, 0);
		}
		
		else if(strcmp(command, "quit") == 0){ //if user wants to quit program
			return false; //quit program
		}
	
	}	

}
