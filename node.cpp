#include "Node.h"
#include <cstddef>

Node::Node(){
	left = NULL;
	right = NULL;
	parent = NULL;
	data;
}



Node* Node::getRight(){
	return right;
}

Node* Node::getLeft(){
	return left;
}

Node* Node::getParent(){
	return parent;
}



int Node::getData(){
	return data;
}

void Node::setData(int newData){
	data = newData;
}



void Node::setRight(Node* newRight){
	right = newRight;
}

void Node::setLeft(Node* newLeft){
	left = newLeft;
}

void Node::setParent(Node* newParent){
	parent = newParent;
}
