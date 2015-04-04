#include "Header.h"
#include <iostream>
//#include <fstream>
//#include <sstream>
#include <vector>

BST::BST()
{
	this->sorted;
	this->comparisons;
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
		comparisons++;
		return Search(root->left, data);
	}
	else 
	{
		comparisons++;
		return Search(root->right, data);
	}
}

void BST::Print_InOrder(Node* root)
{
	if (root != NULL)
	{
		Print_InOrder(root->left);		// left leaf
		std::cout << root->data << " ";	// node
		get_sorted(root);	// fills ascendingVec with each node's data value in ascending order
		Print_InOrder(root->right);		// right leaf
	}
}

void BST::Print_PreOrder(Node* root)
{
	if (root != NULL)
	{
		std::cout << root->data << " ";	// node
		Print_PreOrder(root->left);		// left leaf
		Print_PreOrder(root->right);	// right leaf
	}
}

void BST::Print_PostOrder(Node* root)
{
	if (root != NULL)
	{
		Print_PostOrder(root->left);	// left leaf
		Print_PostOrder(root->right);	// right leaf
		std::cout << root->data << " ";	// node
	}
}

std::vector<int> BST::get_sorted(Node* root)
{
	sorted.push_back(root->data);

	return sorted;
}

void BST::print_sortedVec()
{
	for (int a = 0; a < 150; a++)
	{
		std::cout << sorted[a] << " ";
	}
	std::cout << std::endl;
}

void BST::resetBSTcomparison()
{
	comparisons = 0;
}

int BST::getBSTcomparison()
{
	return comparisons;
}