#include "Header.h"
#include <iostream>

BST::BST()
{
	
}

Node* BST::GetNewNode(int data)	// creates a new Node in heap
{
	Node* newNode = new Node();
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;  
}

Node* BST::Insert(Node* root, int data)	// Inserts data in BST, returns address of root node
{
	if (root == NULL)	// empty tree
	{
		root = GetNewNode(data);
	}
	else if (data <= root->data)	// if data to be inserted is lesser, insert in left subtree
	{
		root->left = Insert(root->left, data);
	}
	else	// insert in right subtree 
	{
		root->right = Insert(root->right, data);
	}
	return root;
}

bool BST::Search(Node* root, int data)	// Searches an element in BST, returns true if element is found
{
	if (root == NULL) 
	{
		return false;
	}
	else if (root->data == data) 
	{
		return true;
	}
	else if (data <= root->data) 
	{
		return Search(root->left, data);
	}
	else 
	{
		return Search(root->right, data);
	}
}