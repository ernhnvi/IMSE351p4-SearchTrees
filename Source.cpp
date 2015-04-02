#include "Header.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

bool validate_userFile(string& userFile);
void generate_numFile(string& userFile);
void numFile_to_vector(ifstream& dataFile);

int main()
{
	char entry;

	cout << "                              Main Menu                            " << endl;
	cout << "                                                                   " << endl;
	cout << "   1. Automatically generate file containing 150 random integers.  " << endl;
	cout << "   2. Import and use existing file containing 150 random integers. " << endl;
	cout << "                                                                   " << endl;
	cout << "   c. Close                                                        " << endl;
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
	return 0;
}

bool validate_userFile(string& userFile)
{
	ifstream dataFile(userFile, ios::in);

	if (!dataFile)	// if unable to open file with name user entered
	{
		cout << "Unable to open file " << userFile << endl;
		return false;
	}

	vector<string> ext = { ".txt", ".dat" };

	for (unsigned int e = 0; e < ext.size(); e++)
	{
		if (userFile.substr(userFile.length() - 4) == ext[e])	// looks at last 4 characters of userFile entry and checks if they match any element in ext array
		{
			cout << "located file" << endl;
			numFile_to_vector(dataFile);
			dataFile.close();
			return true;
		}
		else if (e == ext.size() - 1)		// if no extension found after iterating through last extension in ext vector or user entry is less than 4
		{
			cout << "File name entry does not contain a valid file extension (.txt / .dat)" << endl;
			return false;
		}
	}
}

void generate_numFile(string& userFile)
{
	ofstream numFile(userFile, ios::out);

	srand((unsigned int)time(NULL));	// use system time as seed for rand(), otherwise rand() produces the same number repeatedly

	for (unsigned int x = 0; x < 150; x++)
	{
		int num = rand() % 100 + 1;	// generate random number between 1 and 100
		numFile << num << " ";
	}
	numFile.close();
}

void numFile_to_vector(ifstream& dataFile)
{
	string line;
	getline(dataFile, line);
	stringstream ss(line);

	vector<int> numVec((istream_iterator<int>(ss)), (istream_iterator<int>()));
	
	for (unsigned int x = 0; x < numVec.size(); x++)
	{
		cout << numVec[x] << " ";
	}
}