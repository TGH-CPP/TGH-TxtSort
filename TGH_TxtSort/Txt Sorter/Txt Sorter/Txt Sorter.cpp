// Txt Sorter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void section_command(string Cmd, string &wd1, string &wd2)
{
	string sub_str;
	vector<string> words;
	char search = ' ';
	size_t i, j;

	// Split Command into vector
	for (i = 0; i < Cmd.size(); i++)
	{
		if (Cmd.at(i) != search)
		{
			sub_str.insert(sub_str.end(), Cmd.at(i));
		}
		if (i == Cmd.size() - 1)
		{
			words.push_back(sub_str);
			sub_str.clear();
		}
		if (Cmd.at(i) == search)
		{
			words.push_back(sub_str);
			sub_str.clear();
		}
	}
	// Clear out blanks
	for (i = words.size() - 1; i > 0; i--)
	{
		if (words.at(i) == "")
		{
			words.erase(words.begin() + i);
		}
	}
	// Make words upper case
	for (i = 0; i < words.size(); i++)
	{
		for (j = 0; j < words.at(i).size(); j++)
		{
			if (islower(words.at(i).at(j)))
			{
				words.at(i).at(j) = toupper(words.at(i).at(j));
			}
		}
	}
	// Get 2 words.
	if (words.size() == 0)
	{
		cout << "No command given" << endl;
	}
	if (words.size() == 1)
	{
		wd1 = words.at(0);
	}
	if (words.size() == 2)
	{
		wd1 = words.at(0);
		wd2 = words.at(1);
	}
	if (words.size() > 2)
	{
		cout << "Command too long. Only type one or two words (verb and noun)" << endl;
	}
}

void turnAround(vector<string> &myArr){
	for (int i = 0; i < myArr.size(); i++){
		string line = myArr.at(i);
		int spacePosition = line.find(" ");
		myArr.at(i) = line.substr(spacePosition + 1) + " " + line.substr(0, spacePosition);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	string command;
	string word_1;
	string word_2;
	bool initialized = false;

	while (word_1 != "QUIT"){
		command.clear();
		if (!initialized){
			cout << "Welcome to the official Text Sorting Simulator 2014" << endl << "Here you can 'sort asc', 'show text' and 'quit'" << endl;
			initialized = true;
		}

		getline(cin, command);
		cout << "Your raw command was " << command << endl;
		section_command(command, word_1, word_2);
		if (word_1 == "SORT"){
			if (word_2 == "ASC"){
				string line;
				ifstream infile;
				vector<string> myArr;
				infile.open("names.txt");
				if (infile.is_open()){
					while (getline(infile, line))
					{
						myArr.push_back(line);
					}
					turnAround(myArr);
					sort(myArr.begin(), myArr.end());
					cout << endl << endl;
					turnAround(myArr);
					ofstream oufile;
					oufile.open("names.txt");
					for (int i = 0; i < myArr.size(); i++){
						oufile << myArr.at(i) << endl;
					}
					oufile.close();
					cout << "TextFile has been sorted! (hopefully)" << endl;
				}
				else{
					cout << "R.I.P. File" << endl;
				}
				infile.close();
			}
		}
		else if (word_1 == "SHOW"){
			if (word_2 == "TEXT"){
				string line;
				ifstream infile;
				infile.open("names.txt");
				if (infile.is_open()){
					while (getline(infile, line))
					{
						cout << line << endl;
					}
				}
				else{
					cout << "R.I.P. File" << endl;
				}
				infile.close();
			}
		}
	}
	return 0;
}

