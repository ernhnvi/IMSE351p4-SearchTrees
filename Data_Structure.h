#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTRE_H

#include <vector>

struct Node 
{
	int data;
	Node* left;
	Node* right;
};

class DataStructure
{
public:
	DataStructure();

	void unsorted_fill(std::string &fileName);
	void unsorted_print();
	bool unsorted_search(int &numEntry);

	void fillTree(Node* &root);
	Node* searchTree_newNode(int data);
	Node* searchTree_Insert(Node* root, int data);
	bool searchTree_Search(Node* root, int data);
	void searchTree_printInOrder(Node* root);
	void searchTree_printPreOrder(Node* root);
	void searchTree_printPostOrder(Node* root);

	void sorted_fill(Node* root);
	void sorted_print();
	bool sorted_binarySearch(int &numEntry);

	int comparisonCount();
	void comparisonReset();

	std::vector<int> unsorted;
	std::vector<int> sorted;
	int comparisons;
};

#endif 