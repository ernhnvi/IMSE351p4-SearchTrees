#ifndef HEADER_H
#define HEADER_H

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
};

#endif 