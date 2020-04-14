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
 
Node* addNode(Node**, Node*, int);
void printTree(Node*, int);
Node* fixTree(Node**, Node*);
Node* rotateTree(Node**, Node*, int);
 
 
using namespace std;
 
 
 
Node* addNode(Node** head, Node* parent, int input){ //insert pseudo: https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
    if(parent->getData() == NULL){
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
                //cout << "fixtree input less than parent. ";
                return ((fixTree(head, tempNode))); //rotate
            }
            else{
                addNode(head, parent->getLeft(), input); //call recursively to the left until no left child
            }
        }
        else{ //if the input is greater than or equal to the previous
            //cout << "here. ";
            if(parent->getRight() == NULL){ //if no right child
                Node* tempNode = new Node();
                tempNode->setData(input);
                tempNode->setParent(parent);
                parent->setRight(tempNode);
                //cout << "fixtree input greater or equal to parent. ";
                return ((fixTree(head, tempNode))); //rotate
            }
            else{
                addNode(head, parent->getRight(), input); //call recursively to the right until no right child
            }
        }
    }
    //    head->setColor(0);
    return (*(head));
}
 
 
 
void printTree(Node* parent, int space){ //sideways tree print algorithm (same as bst)
    
    if(parent == NULL){ //dont print an empty tree
        cout << "(tree is empty)" << endl;
        return;
    }
    
    if(parent->getRight() != NULL){
        printTree(parent->getRight(), space+1);
    }
    
    int n = space; //count variable
    
    
    while(space > 0){ //print spaces
        cout << "    ";
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
 
 
 
Node* fixTree(Node** head, Node* current){ //check and fix tree after every insertion
    
    //Node* parent = NULL;
    //Node* grandparent = NULL;
    Node* parent = current->getParent(); //declare parent
    Node* grandparent = parent->getParent(); //declare grandparent
    
    //if current is the root, do nothing
    while(current != *head && parent != NULL && parent->getColor() == 0){
        
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
                if(current == parent->getRight()){ //if current is right child
                    cout << "rotate tree left" << endl;
                    current = parent;
                    cout << "##currentnode is " << current->getData() << endl;
                    return rotateTree(head, current, 0);    //SEGFAULT
                    parent = current->getParent(); //parents
                }
                //current is left child
                cout << "rotate tree right grandparent" << endl;
                rotateTree(head, grandparent, 1); //SEGFAULT
                int tempColor = parent->getColor();
                //parent->setColor(1);
                //grandparent->setColor(0);
                parent->setColor(grandparent->getColor());
                grandparent->setColor(tempColor);
                current = parent;
            }
            //uncle = NULL;
            //delete uncle; //mem
        }
        
        else{ //if parent is right childe
            
            Node* uncle = grandparent->getLeft();
            
            //same as parent left child
            if(uncle != NULL && uncle->getColor() == 0){ //if uncle is red
                //Node* input = new Node();
                //input = uncle;
                
                parent->setColor(1);
                //input->setColor(1);
                uncle->setColor(1);
                grandparent->setColor(0); //grand parent red
                current = grandparent;
            }
            else{ //if uncle is black
                if(current == parent->getLeft()){ //if current is left child
                    cout << "rotate tree right" << endl;
                    current = parent; //current is now the PARENT
                    //cout << "##currentnode is " << current->getData() << endl;
                    //return rotateTree(head, current, 1); //SEGFAULT
					rotateTree(head, current, 1);
                    //parent = current->getParent;
                }
                //current is right child
                cout << "rotate tree left grandparent" << endl;
                  //SEGFAULT
               // cout << "====================" << endl;
				
                //printTree(rotateTree(head, grandparent, 0), 0);
				
				//rotateTree(head, grandparent, 0);
				
				//cout << "current (rightmost, 3): " << current->getData() << endl;
				//cout << "current's (rightmost, 3) COLOR: " << current->getColor() << endl;
				
                int tempColor = parent->getColor();
                //parent->setColor(grandparent->getColor());
                //grandparent->setColor(tempColor);
				parent->setColor(1);
                grandparent->setColor(0);
				current->setColor(0);
				
				//cout << "current (rightmost, 3): " << current->getData() << endl;
				//cout << "current's (rightmost, 3) COLOR: " << current->getColor() << endl;
				
				rotateTree(head, grandparent, 0);
				
				//for some reason i need these two lines:
				/*current->setColor(1);
				current->getRight()->setColor(0);
				break;*/
				
				
				//parent->setColor(1);
				//grandparent->setColor(0);
				//current->setColor(1);
				//(*head)->setColor(1);
				return (*(head)); //needs to break out for some reason
            }
            //uncle = NULL;
            //delete uncle;
        }
        
    }
    
    //cout << "got here" << endl;
    
    /*parent = NULL;
    grandparent = NULL;
    delete parent;
    delete grandparent;*/
    
    (*head)->setColor(1); //root is always black
    
	/*cout << "what is the head? it's " << (*head)->getData() << endl;
    
    if((*head)->getParent() != NULL){
        *head = parent;
    }
    
    cout << "what is the head? it's " << (*head)->getData() << endl;*/
    
    return (*(head));
}
 
 
 
 
 
Node* rotateTree(Node** head, Node* current, int leftright){ //ISSUE IS IN THE ROTATION FUNCTION
    
    //0 is left, 1 is right
    if(leftright == 0){ //left rotation       
	
		//ERROR WHEN ROTATE LEFT GRANDPARENT, COLORS ARE WRONG??
		
		
        //cout << "did i get here? i did!" << endl;
        
        //cout << "##current's right child is " << current->getRight()->getData() << endl;
        
        Node* rightNode = current->getRight(); //current's right child
		//cout << "rightNode's right COLOR: " << rightNode->getRight()->getColor() << endl;
        //cout << "hey. i actually got here!" << endl;
        
		current->setRight(rightNode->getLeft());    
        
        //what is rightNode left child???
        
        if(rightNode->getLeft() != NULL){
            rightNode->getLeft()->setParent(current);
        }
        
        //current->setRight(rightNode->getLeft()); //test
        
        rightNode->setParent(current->getParent());
        
        //printTree(*head, 0);
		/*cout << "current: " << current->getData() << endl;
		if(current->getParent() != NULL){
			cout << "parent: " << current->getParent()->getData() << endl;	
		}
        cout << "rightNode: " << rightNode->getData() << endl;
		cout << "rightNode's right: " << rightNode->getRight()->getData() << endl;
		cout << "rightNode's right COLOR: " << rightNode->getRight()->getColor() << endl;
		*/
		
        
        if(current == (*(head))){
            (*(head)) = rightNode;
        }
        else{
            if(current == current->getParent()->getLeft()){
                current->getParent()->setLeft(rightNode);
            }
            else{
                current->getParent()->setRight(rightNode);
            }
        }
        
        rightNode->setLeft(current);
        current->setParent(rightNode);
		
        //printTree(*head, 0);
		rightNode->setColor(1); //THIS FIXES IT!!!
        
    }
    
    
    
    else if(leftright == 1){ //right rotation
        Node* leftNode = current->getLeft();
        
        cout << current->getLeft()->getData() << endl;
        
        current->setLeft(leftNode->getRight());    //SEGFAULT IS THROWN HERE.
        if(leftNode->getRight() != NULL){
            leftNode->getRight()->setParent(current);
        }
        leftNode->setParent(current->getParent());
        if(current == (*(head))){
            (*(head)) = leftNode;
        }
        else{
            if(current == current->getParent()->getLeft()){
                current->getParent()->setLeft(leftNode);
            }
            else{ //must be right
                current->getParent()->setRight(leftNode);
            }
        }
        leftNode->setRight(current);
        current->setParent(leftNode);
		
        //printTree(*head, 0);
    }
    
    return *head;
}
 
 
 
 
 
 
 
//bool searchTree(Node* ){
    //not now
//}
 
 
 
//Node* deleteNode(Node* head, int number){
    //later
//}
 
 
int main(){
    
    Node* head = new Node;
    
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
            head = ((addNode(&head, head, number)));
            //cout << ":" <<endl;
            //cout << head -> getData() << endl;
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
