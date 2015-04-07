#include "Data_Structure.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <windows.h>

using namespace std;

#undef max		// windows include defines a macro max(), need to undefine it to use max in line 71 to ignore user entry if invalid

string generate_numFile();
string validate_userFile();
void fillTree(Node* &root);
void printTree(DataStructure &ds, Node* &root);
int numEntry(DataStructure &ds, Node* &root);

int main()
{
		int entry;

		string file;

		cout << endl;
		cout << "                              Main Menu                            " << endl;
		cout << "                                                                   " << endl;
		cout << "   1. Automatically generate file containing 150 random integers.  " << endl;
		cout << "   2. Import and use existing file containing 150 random integers. " << endl;
		cout << "                                                                   " << endl;
		cout << "   3. Close                                                        " << endl;
		cout << endl;
		cout << "   > ";
		cin >> entry;

		if (cin.good())		// if user entry was an integer
		{
			switch (entry)
			{
			case 1:
				file = generate_numFile();
				break;
			case 2:
				file = validate_userFile();
				break;
			case 3:
				break;
			default:
				cout << "\t****INVALID ENTRY****" << endl;
				Sleep(500);
				system("CLS");
				main();
				break;
			}
			if (entry != 3)
			{
				DataStructure ds;
				Node* root = NULL;

				ds.unsorted_fill(file);
				ds.fillTree(root);
				printTree(ds, root);
				numEntry(ds, root);
			}
		}
		else
		{
			cout << "\t****INVALID ENTRY****" << endl;
			Sleep(500);
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// ignore to the end of line for user entry
			system("CLS");
			main();
		}
		
		return 0;
}

string generate_numFile()
{
	string defaultFile_name = "numFile.dat";
	ofstream generatedFile(defaultFile_name, ios::out);

	std::random_device rd;

	for (unsigned int x = 0; x < 150; x++)	// fill fill with 150 integers
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
	cout << "   Enter name of file: ";
	cin >> fileName;

	vector<string> ext = { ".txt", ".dat" };
	vector<string> matchingFiles;

	if (fileName.length() <= 4)
	{
		cout << "\t****INVALID FILE NAME****" << endl;
		Sleep(500);
		system("CLS");
		main();
	}

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
			cout << "\t****UNABLE TO LOCATE FILE****" << endl;
			Sleep(500);
			system("CLS");
			main();
		}

		else if (matchingFiles.size() > 0)
		{
			system("CLS");
			cout << matchingFiles.size() << " potential file(s) detected.\n\tEnter the number cooresponding to the correct filename" << endl;
			cout << "\tOR enter 'm' to select a different option from the menu." << endl;

			int count = 0;
			cout << "\nFile(s) Detected" << endl;
			for (unsigned int x = 0; x < matchingFiles.size(); x++)
			{
				count++;
				cout << "\t(" << count << ") " << matchingFiles[x] << endl;
			}
			cout << endl;
			cin >> response;

			if (response == 'm' || response == 'M')
			{
				system("CLS");
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
				ss >> y;	// convert char entry from response to integer to use it in retrieving the vector index

				return matchingFiles[y - 1];	// subtract 1 because user was presented with file list that began counting from 1
			}
		}
	}
	else if (dataFile)	// able to successfully open the file cooresponding to userFile entry
	{
		dataFile.close();
		return fileName;
	}
}

void printTree(DataStructure &ds, Node* &root)
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
			ds.unsorted_print();
			cout << endl;
			break;
		case 1:
			ds.searchTree_printInOrder(root);
			cout << endl;
			break;
		case 2:
			ds.searchTree_printPreOrder(root);
			cout << endl;
			break;
		case 3:
			ds.searchTree_printPostOrder(root);
			cout << endl;
			break;
		case 4:
			ds.sorted_print();
			cout << endl;
			break;
		default:
			break;
		}
		cout << std::endl;
	}
	//system("PAUSE");
}

int numEntry(DataStructure &ds, Node* &root)
{
	int inCounter = 5;
	int outCounter = 5;
	int numEntry;

	vector<int> inList;
	vector<int> outList;

	while (inList.size() + outList.size() != 10)
	{	
		cout << "Enter " << 10 - (inList.size() + outList.size()) << " numbers" << endl;
		cout << inCounter  << " more matching file data" << endl;
		cout << outCounter << " more NOT matching file data" << endl;
		cin >> numEntry;
		
		system("CLS");

		if (!cin)
		{
			cout << "Invalid character entry." << endl;
			system("PAUSE");
			break;
		}
		else
		{
			bool inFull = false; bool outFull = false;

			while (!inFull || !outFull)
			{
				// Determines if user entry exists in unsorted list, if 5 entries already exist for found/not found numbers
				// Prints unsorted array comparison count for current entry and total comparisons for unsorted array using linear search 
				if (ds.unsorted_search(numEntry))
				{
					if (inCounter == 0)
					{
						cout << "You already entered 5 numbers matching file data." << endl;
						inFull = true;
						system("PAUSE"); system("CLS");
						break;
					}
					else
					{
						cout << "Value: " << numEntry << " FOUND     \t\t   Comparisons \t Total" << endl;
						cout << "Unsorted Array(Linear Search) \t\t" << ds.comparisonCount() << "\t  " << ds.get_linear_total() << endl;
						inList.push_back(numEntry);
						inCounter--;
					}
				}
				else 
				{
					if (outCounter == 0)
					{
						cout << "You already entered 5 numbers NOT matching file data." << endl;
						outFull = true;
						system("PAUSE"); system("CLS");
						break;
					}
					else
					{
						cout << "Value: " << numEntry << " NOT FOUND \t\t   Comparisons \t Total" << endl;
						cout << "Unsorted Array(Linear Search) \t\t" << ds.comparisonCount() << "\t  " << ds.get_linear_total() << endl;
						outList.push_back(numEntry);
						outCounter--;
					}
				}
				ds.comparisonReset();	// resets comparison count to 0

				// Prints search tree comparison count for current entry and total comparisons for search tree using binary search
				ds.searchTree_Search(root, numEntry);
				cout << "Binary Tree(Binary Search) \t\t" << ds.comparisonCount() << "\t  " << ds.get_BST_total() << endl;
				ds.comparisonReset();	// resets comparison count to 0

				// Prints sorted array comaprison count for current entry and total comparisons for sorted array using binary search
				ds.sorted_binarySearch(numEntry);
				cout << "Sorted Array(Binary Search) \t\t" << ds.comparisonCount() << "\t  " << ds.get_BSA_total() << endl;
				ds.comparisonReset();	// resets comparison count to 0

				// Prints lists of user's prior entries
				cout << "\nCurrent Entries" << endl;
				cout << "FOUND list   \t";
				for (unsigned int i = 0; i < inList.size(); i++)
				{
					cout << inList[i] << " ";
				}
				cout << endl;

				cout << "NOT FOUND list\t";
				for (unsigned int i = 0; i < outList.size(); i++)
				{
					cout << outList[i] << " ";
				}
				cout << endl;

				system("PAUSE"); system("CLS");
				break;
			} 
		}
	}
	system("CLS");
	cout << "Results" << endl;
	cout << "Unsorted Array " << ds.get_linear_total() << " LINEAR search comparisons" << endl;
	cout << "Search Tree    " << ds.get_BST_total() << " BINARY search comparisons" << endl;
	cout << "Sorted Array   " << ds.get_BSA_total() << " BINARY search comparisons" << endl;
	
	return 0;
}