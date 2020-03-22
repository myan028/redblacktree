#include "node.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>

/*
Code by Michael Yan
3/7/2020
This code runs a Binary Search Tree algorithm. The user is able to add via console or file, add additional values,
search, or delete.
*/

using namespace std;

int COUNT = 10;



Node* smallestNode(Node* node){ //get the smallest node for delete
	Node* current = node;
	while(current->getLeft()!=NULL){
		current = current->getLeft();
	}
	return current;
}



void addNode(Node* head, int number){ //binary search tree add node algorithm (logic from en.wikipedia.org/wiki/Binary_search_tree)
	//head starts as the root, then becomes current/head to lower level children
	if(head->getData() == NULL){ //if tree is empty before add
		//head = new Node();
		head->setData(number);
		return;
	}
	else{
		if(number > head->getData()){ //if the number being added is larger than current head
			if(head->getRight() == NULL){ //go to right
				head->setRight(new Node());
				head->getRight()->setParent(head);
				head->getRight()->setData(number);
				return;
			}
			else{ //if right exists
				addNode(head->getRight(), number); //perform addNode recursively with the right node
			}
		}
		else if(number < head->getData()){ //if the number being added is smaller than current head
			if(head->getLeft() == NULL){ //go to left
				head->setLeft(new Node());
				head->getLeft()->setParent(head);
				head->getLeft()->setData(number);
				return;
			}
			else{ //if left exists
				addNode(head->getLeft(), number); //perform addNode recursively with the left node
			}
			
		}
		else if(number = head->getData()){ //if the number being added is equal to current head
			if(head->getRight() == NULL){ //equal value also goes to right
				head->setRight(new Node());
				head->getRight()->setParent(head);
				head->getRight()->setData(number);
				return;
			}
			else{ //if right exists
				addNode(head->getRight(), number); //perform addNode recursively with the right node
			}
		}
		else{
			return;	
		}
		
	}
	
}



void printTree(Node* head, int space){ //https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
    
	//sideways tree (no branch graphic)
    if (head == NULL){ //empty tree
		return;
	}
    
    //increase distance between levels
    space += COUNT;
  
    //process right child first
    printTree(head->getRight(), space);
  
    //print current node after space 
    cout << endl;  
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << head->getData() << "\n";
	
    printTree(head->getLeft(), space); //process left child
	
}



bool searchTree(Node* head, Node* headtemp, int number){
	
	if(head->getData() == number){ //check for matching value in each recursion call
		//return true;
		cout << "The value you entered, " << number << ", was found!" << endl; //value was found
	}
	
	else{
		if(head->getLeft() != NULL){
			searchTree(head->getLeft(), headtemp, number);
		}
		else{
			//cout << "yeet" << endl;
			if(headtemp->getRight() != NULL){
				//cout << "yeet" << endl;
				head = headtemp;
				searchTree(head->getRight(), headtemp->getRight(), number);
			}
			else{
				cout << "The value you entered, " << number << ", was not found." << endl; //no matching value found
				//return false;
			}
		}
		
	}
	
	//cout << "The value you entered, " << number << ", was not found." << endl;
	//return false;
}



Node* deleteNode(Node* head, int number){ //delete method //idea to use node class method credit: Jason Shi
  	
	if(head->getLeft() == NULL & head->getRight() == NULL){ //primary case
		head->setData(NULL);
	}
	else if(head->getData() > number){ //if number is less than current
		head->setLeft(deleteNode(head->getLeft(), number));
 	}
	else if(number > head->getData()){ //if number is greater than current
		head->setRight(deleteNode(head->getRight(), number));
	}
	else{ //null children cases
		if(head->getLeft() == NULL){
			Node* temp = head->getRight();
			free(head);
			return temp;
		}
		else if(head->getRight() == NULL){
			Node* temp = head->getLeft();
			free(head);
			return temp;
		}
		
		Node* temp = smallestNode(head->getRight()); //find smallest for swap
		
		head->setData(temp->getData()); //delete and replace
		head->setRight(deleteNode(head->getRight(), temp->getData()));
	}
}



int main(){
	
	char* method = new char[100];
	cout << "Would you like to add numbers manually in the console or via .txt file? Type 'manual' or 'file': ";
	cin.getline(method, 100);
	
	int index = 0;
	int *stor = new int[1000];
	
	if(strcmp(method, "manual") == 0){ //if user wants to enter in the console
		cout << "Type in a number/series of numbers that you would like to add to the tree, separated by spaces:" << endl;
		
		char* input2  = new char[100];		
		cin.getline(input2, 100);
		
		char* token = strtok(input2, " "); //split array into tokens by spaces
		
		while(token != NULL){ //fill stor with tokens
			stor[index] = atoi(token); //convert token into int
			token = strtok(NULL, " "); //clear token
			index++; //increment
		}
		
	}
	
	else if(strcmp(method, "file") == 0){ //if user wants to add from a local .txt file
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

	}
	
	Node* head = new Node();
	Node* headtemp = new Node();
	headtemp = head;
	
	for(int i = 0; i < index; i++){
		addNode(head, stor[i]);
	}	
	
	while(true){ //give user action command options
		cout << "\nEnter a command. Type 'add', 'print', 'search', 'delete', or 'quit': ";
		
		char* command = new char[10];
		cin.getline(command, 10);
		int number = 0;
		
		if(strcmp(command, "add") == 0){ //if user wants to add a value
			cout << "Enter the number you want to add: " <<endl;
			cin >> number;
			cin.get();
			addNode(head, number);
		}
		
		else if(strcmp(command, "print") == 0){ //if user wants to print the tree
			if(head->getData() == NULL){ //if tree is empty
                    cout << "(tree is empty)" << endl;
			}
			else{
				printTree(head, 0); //call printTree
			}
		}
		
		else if(strcmp(command, "search") == 0){ //if user wants to search for a value
			if(head->getData() == NULL){ //if tree is empty
                    cout << "The tree is empty." << endl;
			}
			else{
				cout << "Search for a number: ";
				cin >> number;
				cin.get();
				searchTree(head, headtemp, number);
				/*if(searchTree){
					cout << "Search results negative." << endl;
				}
				else if (searchTree){
					cout << "Search results positive." << endl;
				}*/
			}
		}
		
		else if(strcmp(command, "delete") == 0){ //if user wants to delete a value
			cout << "Enter the number you would like to delete: ";
			cin >> number;
			cin.get();
			head = deleteNode(head, number);
        }
		
		else if(strcmp(command, "quit") == 0){ //if user wants to quit program
			return false; //quit program
		}
	
	}	

}
