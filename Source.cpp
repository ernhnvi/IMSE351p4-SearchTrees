#include "Data_Structure.h"
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
void fillTree(Node* &root);
void printTree(DataStructure &ds, Node* &root);
void numEntry(DataStructure &ds, Node* &root);

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

	DataStructure ds;
	Node* root = NULL;

	ds.unsorted_fill(file);
	ds.fillTree(root);
	printTree(ds, root);
	numEntry(ds, root);

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
	system("PAUSE");
}

void numEntry(DataStructure &ds, Node* &root)
{
	int inCounter = 5;
	int outCounter = 5;
	int numEntry;
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
		cout << inCounter  << " that are from the number list " << endl;
		cout << outCounter << " that are not in the number list" << endl;
		cin >> numEntry;

		if (!cin)
		{
			cout << "Invalid character entry." << endl;
			break;
		}
		else
		{
			bool inFull = false; bool outFull = false;
			while (!inFull || !outFull)
			{
				if (ds.unsorted_search(numEntry))
				{
					if (inCounter == 0)
					{
						cout << "5 number entries that match numbers in list already exist." << endl;
						inFull = true;
						system("PAUSE");
						ds.comparisonReset();
						break;
					}
					else
					{
						cout << "Unsorted: " << ds.comparisonCount() << endl;
					}
				}
				else
				{
					if (outCounter == 0)
					{
						cout << "5 number entries that match numbers in list already exist." << endl;
						outFull = true;
						system("PAUSE");
						ds.comparisonReset();
						break;
					}
					else
					{
						cout << "Unsorted: NOT FOUND" << endl;
					}
				}
				ds.comparisonReset();

				if (ds.searchTree_Search(root, numEntry))
				{
					cout << "BinSearchTree: " << ds.comparisonCount() << endl;
					inCounter--;
				}
				else
				{
					cout << "BinSearchTree: NOT FOUND" << endl;
					outCounter--;
				}
				ds.comparisonReset();

				if (ds.sorted_binarySearch(numEntry))
				{
					cout << "Sorted: " << ds.comparisonCount() << endl;
					inList.push_back(numEntry);
				}
				else
				{
					cout << "Sorted: NOT FOUND" << endl;
					outList.push_back(numEntry);
				}
				ds.comparisonReset();

				system("PAUSE");
				break;
			}
			system("CLS");
			cout << "Entry Complete" << endl;
		}
	}
}