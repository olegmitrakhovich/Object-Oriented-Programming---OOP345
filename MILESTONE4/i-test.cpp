#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

#include "i.h"

int main(int argc, char* argv[])
{
	try {
		if (argc != 3) {
			throw string("Usage ") + argv[0] + string(": filename delimiter-char");
		}

		string filename = string(argv[1]);
		char delimiter = argv[2][0];

		vector <vector<string > > csvItemData;
		csvRead(filename, delimiter, csvItemData);

		ItemManager im(csvItemData);
		im.Print();
		im.Graph(filename);

	}
	catch (const string& e) {
		cerr << e << "\n";
	}
}