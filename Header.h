#ifndef HEADER_H
#define HEADER_H

#include <fstream>

struct Node 
{
	int data;
	Node* left;
	Node* right;
};

class BST
{
public:
	BST();
	Node* GetNewNode(int data);
	Node* Insert(Node* root, int data);
	bool Search(Node* root, int data); 

	void Print_InOrder(Node* root);
	void Print_PreOrder(Node* root);
	void Print_PostOrder(Node* root);
};

#endif 