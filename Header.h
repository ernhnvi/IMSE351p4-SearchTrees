#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <vector>

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

	std::vector<int> get_sorted(Node* root);
	void print_sortedVec();

	void resetBSTcomparison();
	int getBSTcomparison();

	std::vector<int> sorted;
	int comparisons;
};

#endif 