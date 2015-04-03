#include "Header.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <windows.h>

using namespace std;

void menu();
void generate_numFile(string& numFile);
bool validate_userFile(string& userFile);
void numFile_to_vector(string& fileName);

void fillTree(vector<int> numVec);
void printOrderedTree(vector<int> numVec, BST tree, Node* root);

int main()
{
	menu();

	return 0;
}


void menu()
{
	char entry;

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

	string numFile;
	bool extFound = false;

	switch (entry)
	{
	case '1':
		numFile = "numFile.dat";
		generate_numFile(numFile);
		break;
	case '2':
		do {
			cout << "Enter name of file: ";
			cin >> numFile;
			extFound = validate_userFile(numFile);
		} while (!extFound);
		break;
	case 'c':
		break;
	default:
		cout << "Invalid entry." << endl;
	}
}

void generate_numFile(string& numFile)
{
	ofstream generatedFile(numFile, ios::out);

	std::random_device rd;		

	for (unsigned int x = 0; x < 150; x++)
	{
		int num = (rd() % 1000)-500;	// generate random number between +500 and -500
		generatedFile << num << " ";
	}
	generatedFile.close();

	numFile_to_vector(numFile);
}

bool validate_userFile(string& userFile)
{
	vector<string> ext = { ".txt", ".dat" };
	vector<string> detected;

	ifstream dataFile(userFile, ios::in);

	if (!dataFile)
	{
		for (unsigned int e = 0; e < ext.size(); e++)
		{
			if (userFile.substr(userFile.length() - 4) != ext[e])	// if userFile entry does not match a substring equal to the current index of ext vector
			{
				string detectedFileName = userFile + ext[e];	// append the file extension to the end of userFile entry
				
				ifstream fileWithExt(detectedFileName, ios::in);	// set the appended string name as the file to be read

				if (fileWithExt)	// if the file can be opened 
				{
					detected.push_back(detectedFileName);	// add the appended version of userFile entry detected vector
				}
				fileWithExt.close();
			}
		}
		
		char response;

		if (detected.empty())	// if userFile did not contain a matching substring to any index of ext and appending each extension in ext to the end of userFile did not result in a match to an existing file 
		{
			cout << "Unable to locate file." << endl;
			return false;
		}

		else if (detected.size() == 1)	// if, after appending each extension from ext to the end of userFile, 1 match was found with a file in the current directory
		{
			cout << "File extension not detected in entry. Did you mean " << detected[0] << "? (y/n)" << endl;
			cin >> response;

			if ((response == 'y') || (response == 'Y'))
			{
				numFile_to_vector(detected[0]);
				return true;
			}
			else if ((response == 'n') || (response == 'N'))
			{
				cout << "Enter a valid input file name." << endl;
				return false;
			}
			else
			{
				cout << "Invalid entry." << endl;
				menu();
			}
		}
		
		else if (detected.size() > 1)
		{
			cout << detected.size() << " potential files detected. Enter the number cooresponding to the correct filename." << endl;
			
			int count = 1;
			for (unsigned int d = 0; d < detected.size(); d++)
			{
				cout << "(" << count << ") " << detected[d] << endl;
				count++;
			}
			cout << endl;
			cin >> response;

			stringstream ss; 
			ss << response;
			int r;
			ss >> r;		// convert char entry from response to integer to use it in retrieving the vector index

			numFile_to_vector(detected[r - 1]);		// subtract 1 because user was presented with file list that began counting from 1
		}
	}
	else if (dataFile)		// able to successfully open the file cooresponding to userFile entry
	{
		numFile_to_vector(userFile);
		return true;
	}	

	dataFile.close();
}

void numFile_to_vector(string& fileName)
{
	ifstream dataFile(fileName, ios::in);

	string line;
	getline(dataFile, line);
	dataFile.close();

	stringstream ss(line);

	vector<int> numVec((istream_iterator<int>(ss)), (istream_iterator<int>()));		// populate numVec with integers in stringstream ss 
	
	fillTree(numVec);
}

void fillTree(vector<int> numVec)
{
	BST tree;	// create new BST object
	Node* root = NULL; // create empty tree

	for (unsigned int n = 0; n < numVec.size(); n++)
	{
		root = tree.Insert(root, numVec[n]);
	}

	printOrderedTree(numVec, tree, root);
}

void printOrderedTree(vector<int> numVec, BST tree, Node* root)
{
	int width;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int nonZero = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	if (nonZero)
	{
		width = (csbi.dwSize.X);
	}

	vector<string> printLabel = { " FromFile ", " In Order ", " PreOrder ", " Post Order ", " AscendingVec " };

	for (unsigned int p = 0; p < printLabel.size(); p++)
	{
		cout << "\n"; 
		for (int i = 0; i < ((width - printLabel[p].size()) / 2); i++)
		{
			cout << "=";
		}

		cout << printLabel[p];

		for (int i = 0; i < ((width - printLabel[p].size()) / 2); i++)
		{
			cout << "=";
		}
		
		switch (p)
		{
		case 0:
			for (unsigned int x = 0; x < numVec.size(); x++)
			{
				cout << numVec[x] << " ";
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
			tree.print_ascendingVec();
			cout << endl;
			break;
		}
		cout << std::endl;
	}
}