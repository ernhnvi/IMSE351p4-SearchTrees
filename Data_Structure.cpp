#include "Data_Structure.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

DataStructure::DataStructure()
{
	this->unsorted;
	this->sorted;
	this->comparisons;
}

/*------------------------unsorted--------------------------*/

void DataStructure::unsorted_fill(std::string &fileName)
{
	std::ifstream dataFile(fileName, std::ios::in);
	std::string line;
	getline(dataFile, line);
	dataFile.close();
	std::stringstream ss(line);
	std::vector<int>unsorted_temp((std::istream_iterator<int>(ss)), (std::istream_iterator<int>()));

	for (int a = 0; a < unsorted_temp.size(); a++)
	{
		unsorted.push_back(unsorted_temp[a]);
	}
}

void DataStructure::unsorted_print()
{
	for (int a = 0; a < unsorted.size(); a++)
	{
		std::cout << unsorted[a] << " ";
	}
	std::cout << std::endl;
}

bool DataStructure::unsorted_search(int &numEntry)
{
	for (unsigned int x = 0; x < unsorted.size(); x++)
	{
		if (unsorted[x] == numEntry)
		{
			return true;
		}
		else
		{
			comparisons++;
		}
	}
	return false;
}

/*------------------------search tree-----------------------*/

void DataStructure::fillTree(Node* &root)
{
	for (unsigned int n = 0; n < unsorted.size(); n++)
	{
		root = searchTree_Insert(root, unsorted[n]);
	}
}

Node* DataStructure::searchTree_newNode(int data)	// creates a new Node in heap
{
	Node* newNode = new Node();
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

Node* DataStructure::searchTree_Insert(Node* root, int data)
{
	if (root == NULL)	// empty tree
	{
		root = searchTree_newNode(data);
	}
	else if (data <= root->data)	// if data to be inserted is lesser, insert in left subtree
	{
		root->left = searchTree_Insert(root->left, data);
	}
	else	// insert in right subtree 
	{
		root->right = searchTree_Insert(root->right, data);
	}
	return root;
}

bool DataStructure::searchTree_Search(Node* root, int data)	// Searches an element in BST, returns true if element is found
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
		return searchTree_Search(root->left, data);
	}
	else
	{
		comparisons++;
		return searchTree_Search(root->right, data);
	}
}

void DataStructure::searchTree_printInOrder(Node* root)
{
	if (root != NULL)
	{
		searchTree_printInOrder(root->left);	// left leaf
		std::cout << root->data << " ";			// node
		sorted_fill(root);						// fills ascendingVec with each node's data value in ascending order
		searchTree_printInOrder(root->right);	// right leaf
	}
}

void DataStructure::searchTree_printPreOrder(Node* root)
{
	if (root != NULL)
	{
		std::cout << root->data << " ";			// node
		searchTree_printPreOrder(root->left);	// left leaf
		searchTree_printPreOrder(root->right);	// right leaf
	}
}

void DataStructure::searchTree_printPostOrder(Node* root)
{
	if (root != NULL)
	{
		searchTree_printPostOrder(root->left);	// left leaf
		searchTree_printPostOrder(root->right);	// right leaf
		std::cout << root->data << " ";			// node
	}
}

/*------------------------sorted----------------------------*/

void DataStructure::sorted_fill(Node* root)
{
	sorted.push_back(root->data);
}

void DataStructure::sorted_print()
{
	for (int a = 0; a < sorted.size(); a++)
	{
		std::cout << sorted[a] << " ";
	}
	std::cout << std::endl;
}

bool DataStructure::sorted_binarySearch(int &numEntry)
{
	int low = 0;
	int mid;
	int high = sorted.size() - 1;

	while (low <= high)
	{
		mid = (low + high) / 2;

		if (numEntry == sorted[mid])
		{
			return true;
		}
		else if (numEntry > sorted[mid])
		{
			comparisons++;
			low = mid + 1;
		}
		else if (numEntry < sorted[mid])
		{
			comparisons++;
			high = mid - 1;
		}
	}
	return false;
}

/*------------------------shared----------------------------*/

int DataStructure::comparisonCount()
{
	return comparisons;
}

void DataStructure::comparisonReset()
{
	comparisons = 0;
}