/***********************************************
* Mika Peer Shalem, mpeersha
* 2023 Winter CSE101 PA8
* Order.cpp
* Contains a main function that performs operations on a Dictionary
***********************************************/
#include "Dictionary.h"
#include<iostream>
#include <fstream>
#include<string>
using namespace std;
int main(int argc, char * argv[]) {
	ifstream in;
	ofstream out;
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

    string line;
    int count = 1;
	Dictionary D;
	while (getline(in, line)) {
		D.setValue(line, count);
        count += 1;
	}
    out << D.to_string() << endl;
    out << D.pre_string() << endl;
}
