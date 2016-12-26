#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"
// put '|' for pipe symbol

#include "t.h"
using namespace std;


int main(int argc, char* argv[]) {
	try {
		if (argc != 3)
			throw string("usage:") + argv[0] + "file.csv delimeter-char";
		string filename = argv[1]; //1st arg
		char delim = argv[2][0]; //1st char of second arg

		vector< vector <string> > csvTaskData;
		csvRead(filename, delim, csvTaskData);

		csvPrint(csvTaskData);

		TaskManager tm(csvTaskData);
		tm.Print();
		tm.Graph(filename);
	}
	catch (string& e) {
		cerr << e << "\n";
	}

	return 0;
}