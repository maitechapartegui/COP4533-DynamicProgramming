#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

// take input from file to get alphabet values
// like sequence alignment bc you need the common substring /compairsoins being made mismatches and gaps
// like rna secondary structure bc we are going to be splitting it into two different intervals

// RETURN MAXIMUM TOTAL VALUE OF THE CHARACTERS WITHIN A SUBSTRING

int main(int argc, char** argv) {
	// Read in file information
	if(argc < 2){
		cout << "Invalid input" << endl;
		return 1;
	}
	string filename = argv[1];

	ifstream in(filename);
	if(!in){
		throw runtime_error("Could not open input file");
	}

	//empty file?
	if (in.peek() == ifstream::traits_type::eof()) {
		throw runtime_error("empty file");
	}

	// first line should be numver of letters
	int numofAlphabets;
	if (!(in >> numofAlphabets)) {
		throw runtime_error("Could not read K");
	}
	// get all the alphabet values create a dictonary/map wher alphabet['a'] = 4
	unordered_map<char, int> alphabetValues;
	char currentLetter;
	int currentValue = 0;
	for (int i = 0; i < numofAlphabets; ++i) {
		if (in >> currentLetter >> currentValue ) {
			alphabetValues[currentLetter] = currentValue;
		}
		else {
			//umm make sure we get them all?
			throw runtime_error("Didnt read entire alphabet");
		}
	}

	// get strings
	string stringA;
	string stringB;
	in >> stringA;
	in >> stringB;
	//OPT: max total value of all possible substrings with i characters from A and j chracters of B
	// Recusive functions - Bottom up!! remember
	// if they match: values are the same so add the values v + opt(i-1, j-1)
	// if they dont match: find max of basically skipping either letter max ( opt(i,j-1) , opt(i-1, j) )

	//OPT: go through every number that is not the length so while we are not at the max lenght of A or B THEN....

	//opt 2d array:
	vector<vector<int>> M;
	// TODO: NEED BASE CASES
	int matchCost = 0;
	int notMatchCost = 0;
	for (int i = 0; i < stringA.length(); ++i) {
		for (int j = 0; j < stringB.length(); ++j) {
			//FIRST need to check if substring are equal
			if (stringA[i] == stringB[j]) {
				// handle subproblems!
				//v + opt(i-1, j-1)
				// NEED THE CHARACTER so we do stringA[i]
				int value = alphabetValues[stringA[i]];
				// need the index in M so we do [i][j] not stringA[i]
				matchCost = value + M[i-1][j-1];
			}
			else {
				//TODO: fix this cause this cant be right?
				//max ( opt(i,j-1) , opt(i-1, j) )
				notMatchCost = max()
			}
			M[stringA[i]][stringB[j]] = max (matchCost,notMatchCost);
		}
	}
	// return that max final value which will be m x n
	maxFinalValue = M[stringA.length() - 1][stringB.length() - 1];

	// TODO: NEED TO DO BACKTRACKING TO RETURN CORRESPONDING SUBSEQUENCE

}