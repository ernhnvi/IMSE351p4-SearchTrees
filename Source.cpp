#include "Header.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <windows.h>

using namespace std;

string generate_numFile();
string validate_userFile();
vector<int> numFile_to_vector(string& fileName);
void fillTree(vector<int> unsorted, BST &tree, Node* &root);
void printOrderedTree(vector<int> unsorted, BST &tree, Node* &root);
void numEntry(BST &tree, Node* &root, vector<int> &unsorted);

void unsorted_comparisons(vector<int> &unsorted, int &numEntry);
void BST_comparisons(BST &tree);
void sorted_comparison(BST &tree, Node* &root, int &numEntry);

int main()
{
	char entry;
	string file;

	cout << endl;
	cout << "                              Main Menu                            " << endl;
	cout << "                                                                   " << endl;
	cout << "   1. Automatically generate file containing 150 random integers.  " << endl;
	cout << "   2. Import and use existing file containing 150 random integers. " << endl;
	cout << "                                                                   " << endl;
	cout << "   c. Close                                                        " << endl;
	cout << endl;
	cout << "   > ";
	cin >> entry;

	switch (entry)
	{
	case '1':
		file = generate_numFile();
		break;
	case '2':
		file = validate_userFile();
		break;
	case 'c':
		break;
	default:
		cout << "Invalid entry." << endl;
		break;
	}

	BST tree;
	Node* root = NULL;
	vector<int> unsorted = numFile_to_vector(file);

	fillTree(unsorted, tree, root);
	printOrderedTree(unsorted, tree, root);

	numEntry(tree, root, unsorted);

	return 0;
}

string generate_numFile()
{
	string defaultFile_name = "numFile.dat";
	ofstream generatedFile(defaultFile_name, ios::out);

	std::random_device rd;

	for (unsigned int x = 0; x < 150; x++)
	{
		int num = (rd() % 1000) - 500;	// generate random number between +500 and -500
		generatedFile << num << " ";
	}
	generatedFile.close();

	return defaultFile_name;
}

string validate_userFile()
{
	string fileName;
	cout << "Enter name of file: ";
	cin >> fileName;

	vector<string> ext = { ".txt", ".dat" };
	vector<string> matchingFiles;
	ifstream dataFile(fileName, ios::in);

	if (!dataFile)
	{
		for (unsigned int e = 0; e < ext.size(); e++)
		{
			if (fileName.substr(fileName.length() - ext[e].size()) != ext[e])	// if userFile entry does not match a substring equal to the current index of ext vector
			{
				string fileName_wExt = fileName + ext[e];	// append the file extension to the end of userFile entry

				ifstream file_wExt(fileName_wExt, ios::in);	// set the appended string name as the file to be read

				if (file_wExt)	// if the file can be opened 
				{
					matchingFiles.push_back(fileName_wExt);	// add the appended version of userFile entry detected vector
				}
				file_wExt.close();
			}
		}
		
		char response;

		if (matchingFiles.empty())	// if userFile did not contain a matching substring to any index of ext and appending each extension in ext to the end of userFile did not result in a match to an existing file 
		{
			cout << "Unable to locate file." << endl;
			Sleep(350);
			system("CLS");
			main();
		}

		else if (matchingFiles.size() > 0)
		{
			cout << matchingFiles.size() << " potential file(s) detected. Enter the number cooresponding to the correct filename or 'm' to return to the menu." << endl;

			int count = 0;
			for (unsigned int x = 0; x < matchingFiles.size(); x++)
			{
				count++;
				cout << "(" << count << ") " << matchingFiles[x] << endl;
			}
			cout << endl;
			cin >> response;

			if (response == 'm' || response == 'M')
			{
				main();
			}
			else if ((int(response) - 48) > count)
			{
				cout << "Invalid entry" << endl;
				Sleep(350);
				system("CLS");
				main();
			}
			else
			{
				stringstream ss;
				ss << response;
				int y;
				ss >> y;		// convert char entry from response to integer to use it in retrieving the vector index

				return matchingFiles[y - 1];	// subtract 1 because user was presented with file list that began counting from 1
			}
		}
	}
	else if (dataFile)		// able to successfully open the file cooresponding to userFile entry
	{
		dataFile.close();
		return fileName;
	}
}

vector<int> numFile_to_vector(string& fileName)
{
	ifstream dataFile(fileName, ios::in);
	string line;
	getline(dataFile, line);
	dataFile.close();
	stringstream ss(line);
	vector<int>unsorted_temp((istream_iterator<int>(ss)), (istream_iterator<int>()));		// populate unsorted with integers in stringstream ss 
	
	return unsorted_temp;
}

void fillTree(vector<int> unsorted, BST &tree, Node* &root)
{
	for (unsigned int n = 0; n < unsorted.size(); n++)
	{
		root = tree.Insert(root, unsorted[n]);
	}
}

void printOrderedTree(vector<int> unsorted, BST &tree, Node* &root)
{
	int width;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int nonZero = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	if (nonZero)
	{
		width = (csbi.dwSize.X);
	}

	vector<string> printLabel = { " FromFile ", " In Order ", " PreOrder ", " Post Order ", " AscendingOrder " };

	for (unsigned int p = 0; p < printLabel.size(); p++)
	{
		cout << "\n";
		for (unsigned int i = 0; i < ((width - printLabel[p].size()) / 2); i++)
		{
			cout << "=";
		}

		cout << printLabel[p];

		for (unsigned int i = 0; i < ((width - printLabel[p].size()) / 2); i++)
		{
			cout << "=";
		}

		switch (p)
		{
		case 0:
			for (unsigned int x = 0; x < unsorted.size(); x++)
			{
				cout << unsorted[x] << " ";
			}
			cout << endl;
			break;
		case 1:
			tree.Print_InOrder(root);
			cout << endl;
			break;
		case 2:
			tree.Print_PreOrder(root);
			cout << endl;
			break;
		case 3:
			tree.Print_PostOrder(root);
			cout << endl;
			break;
		case 4:
			tree.print_sortedVec();
			cout << endl;
			break;
		}
		cout << std::endl;
	}
	system("PAUSE");
}

void numEntry(BST &tree, Node* &root, vector<int> &unsorted)
{
	int numEntry;
	int inCounter = 5;
	int outCounter = 5;

	vector<int> inList;
	vector<int> outList;

	while (inList.size() + outList.size() != 10)
	{
		system("CLS");
		cout << "Found In List\t";
		for (unsigned int i = 0; i < inList.size(); i++)
		{
			cout << inList[i] << " ";
		}
		cout << endl;

		cout << "Not In List\t";
		for (unsigned int i = 0; i < outList.size(); i++)
		{
			cout << outList[i] << " ";
		}
		cout << "\n\n";

		cout << "Enter " << 10 - inList.size() + outList.size() << " numbers" << endl;
		cout << inCounter << " that are from the number list " << endl;
		cout << outCounter << " that are not in the number list" << endl;
		cin >> numEntry;

		if (!cin)
		{
			cout << "Invalid character entry." << endl;
			break;
		}
		else
		{
			if (tree.Search(root, numEntry) && inCounter != 0)
			{
				inCounter--;
				inList.push_back(numEntry);
				unsorted_comparisons(unsorted, numEntry);
				BST_comparisons(tree);
				sorted_comparison(tree, root, numEntry);
			}
			else if (tree.Search(root, numEntry) && inCounter == 0)
			{
				cout << "5 number entries that match numbers in list already exist." << endl;
				system("PAUSE");
			}

			else if (!tree.Search(root, numEntry) && outCounter != 0)
			{
				outCounter--;
				outList.push_back(numEntry);
				unsorted_comparisons(unsorted, numEntry);
				BST_comparisons(tree);
				sorted_comparison(tree, root, numEntry);
			}
			else if (!tree.Search(root, numEntry) && outCounter == 0)
			{
				cout << "5 number entries that do not match numbers in list already exist." << endl;
				system("PAUSE");
			}
		}
	}
	if (inList.size() + outList.size() == 10)
	{
		system("CLS");
		cout << "Entry Complete" << endl;
	}
}

void unsorted_comparisons(vector<int> &unsorted, int &numEntry)
{
	for (unsigned int x = 0; x < unsorted.size(); x++)
	{
		if (unsorted[x] == numEntry)
		{
			cout << "unsorted: " << x << endl;
			break;
		}
		else if ((x == unsorted.size() - 1) && unsorted[x] != numEntry)
		{
			cout << "Unsorted: IMPOSSIBRU!!!" << endl;
		}
	}
}

void BST_comparisons(BST &tree)
{
	cout << "BST: " << tree.getBSTcomparison() << endl;
	tree.resetBSTcomparison();
}

void sorted_comparison(BST &tree, Node* &root, int &numEntry)
{
	vector<int> sorted = tree.get_sorted(root);

	int low = 0;
	int mid;
	int high = sorted.size() - 1;

	int comparisons = 0;

	while (low <= high)
	{
		mid = (low + high) / 2;

		if (numEntry == sorted[mid])
		{
			cout << "Sorted: " << comparisons << endl;
			system("PAUSE");
			break;
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

	if (low > high)
	{
		cout << "Sorted: not found" << endl;
		system("PAUSE");
	}
}