#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <chrono>

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

	//create the output file
	//use the name to be the same
	string outputFile;
	size_t lastDot = filename.find_last_of(".");
	if (lastDot != string::npos) {
		outputFile = filename.substr(0,lastDot) + ".out";
	}
	else {
		outputFile = filename + ".out";
	}

	//OPT: max total value of all possible substrings with i characters from A and j chracters of B
	// Recusive functions - Bottom up!! remember
	// if they match: values are the same so add the values v + opt(i-1, j-1)
	// if they dont match: find max of basically skipping either letter max ( opt(i,j-1) , opt(i-1, j) )

	//OPT: go through every number that is not the length so while we are not at the max lenght of A or B THEN....

	//opt 2d array:
	vector<vector<int>> M;
	M.resize(stringA.length() + 1, vector<int>(stringB.length() + 1, 0));
	// base cases similar to alignment problem:
	for (int i = 0; i < stringA.length(); ++i) {
		M[i][0] = 0;
	}
	for (int j = 0; j < stringB.length(); ++j) {
		M[0][j] = 0;
	}

	// START THE ALGORITHMN
	auto start = chrono::high_resolution_clock::now();
	for (int i = 1; i <= stringA.length(); ++i) {
		for (int j = 1; j <= stringB.length(); ++j) {
			//FIRST need to check if substring are equal
			if (stringA[i-1] == stringB[j-1]) {
				// handle subproblems!
				//v + opt(i-1, j-1)
				// NEED THE CHARACTER so we do stringA[i]
				int value = alphabetValues[stringA[i-1]];
				// need the index in M so we do [i][j] not stringA[i]
				M[i][j] = value + M[i-1][j-1];
			}
			else {
				//max ( opt(i,j-1) , opt(i-1, j) )
				M[i][j] = max(M[i][j-1], M[i-1][j]);
			}
		}
	}
	// return that max final value which will be m x n
	int maxFinalValue = M[stringA.length()][stringB.length()];
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	// need to print this final value
	ofstream out(outputFile);
	out << maxFinalValue << endl;
	out.close();
	cout<< "Max Final value: " << maxFinalValue << endl;
	cout << "file:" <<  outputFile << endl << ", time: in ns " << duration.count() << endl;



	// BACKTRACKING
	// walk backwards from M[m][n]
	// then need to check if letters match and if the value makes sense

	string subseq;
	int i = stringA.length();
	int j = stringB.length();

	while(i > 0 && j > 0) {
		// if chars match 
		if(stringA[i - 1] == stringB[j - 1]){
			int value = alphabetValues[stringA[i - 1]];
			// check if cell came from diagonal plus value -> take this char
			if(M[i][j] == M[i - 1][j - 1] + value){
				subseq.push_back(stringA[i - 1]);
				// move diagonally
				i--;
				j--;
				continue;
			}	
		}

		// didnt take char bc dont match -> move ib direction of where the max val came from
		if (M[i - 1][j] >= M[i][j - 1]){
			// go up
			i--;
		}
		else{
			// go left
			j--;
		}
	}

	reverse(subseq.begin(), subseq.end());

	// write max value and subseq
	out.open(outputFile, ios::app);
	out << subseq << endl;
	out.close();
	cout << "Subsequence: " << subseq << endl;

	return 0;
}