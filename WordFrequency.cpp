/***********************************************
* Mika Peer Shalem, mpeersha
* 2023 Winter CSE101 PA8
* WordFrequency.cpp
* Contains a main function that counts the number of appearences of a word in a text and saves it to a dictionary.
***********************************************/
#include "Dictionary.h"
#include<iostream>
#include <fstream>
#include<string>
#include <cstring>
using namespace std;
int main(int argc, char * argv[]) {
	// int token_count;
    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string line;
    // string tokenBuffer;
    string token;
	string delim = " \t\\\"\',<.>/?;:[{]}|`~!@%#$^&*()-_=+0123456789"; 
	// Check that there are two command line arguments
	// argc = argument count. Stores num of args including program name
	if (argc!=3) {
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return (EXIT_FAILURE);
	}
	// Open input file
	in.open(argv[1]);
	if (!in.is_open()) {
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return (EXIT_FAILURE);
	}
	// Open output file
	out.open(argv[2]);
	if (!out.is_open()) {
		cerr << "Unable to open file " << argv[2] << " for reading" << endl;
		return (EXIT_FAILURE);
	}

	Dictionary D;
	while (getline(in, line)) {
		// get tokens in this line
		len = line.length();
		// get first token
		begin = min(line.find_first_not_of(delim, 0), len);
		end   = min(line.find_first_of(delim, begin), len);
		token = line.substr(begin, end-begin);
		// string newToken; 
		for (size_t i=0; i<token.length(); i+=1) {
			token[i] = tolower(token[i]);
		}
		if (token != "" && D.contains(token)) {
			D.setValue(token, D.getValue(token)+1);
		} else if (token!="") {
			D.setValue(token, 1);
		}
		// cout << "Token is: " << token << endl;

		while( token!=""){  // we have a token
			// get next token
			begin = min(line.find_first_not_of(delim, end+1), len);
			end   = min(line.find_first_of(delim, begin), len);
			token = line.substr(begin, end-begin);
			for (size_t i=0; i<token.length(); i+=1) {
				token[i] = tolower(token[i]);
			}
			if (token!="" && D.contains(token)) {
			D.setValue(token, D.getValue(token)+1);
			} else if (token!="") {
				D.setValue(token, 1);
			}
		}
	}
    out << D.to_string() << endl;
    // out << D.pre_string() << endl;
}
