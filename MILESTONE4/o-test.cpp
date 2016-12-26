#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

#include "o.h"

int main(int argc, char*argv[])
{
	try {
		if (argc != 3) {
			throw string("Usage ") + argv[0] + string(": filename delimiter-char");
		}

		string filename = string(argv[1]);
		char delimiter = argv[2][0];

		vector < vector<string > > csvOrderData;
		csvRead(filename, delimiter, csvOrderData);

		OrderManager om(csvOrderData);
		om.Print();
		om.Graph(filename);

	}
	catch (const string& e) {
		cerr << e << "\n";
	}
}