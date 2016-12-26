#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

#include "i.h"
#include "o.h"
#include "t.h"

int main(int argc, char* argv[])
{
	try {
		if (argc != 5) {
			throw string("usage ") + argv[0] + string(": item order task (the 3 csv files) delimiter-char");
		}

		string filenameItem = string(argv[1]);
		string filenameOrder = string(argv[2]);
		string filenameTask = string(argv[3]);
		char delimiter = argv[4][0];

		vector <vector <string > > csvItemData;
		vector < vector< string > > csvOrderData;
		vector < vector< string > > csvTaskData;

		csvRead(filenameItem, delimiter, csvItemData);
		csvRead(filenameOrder, delimiter, csvOrderData);
		csvRead(filenameTask, delimiter, csvTaskData);

		ItemManager im(csvItemData);
		im.Print();
		im.Graph(filenameItem);

		OrderManager om(csvOrderData);
		om.Print();
		om.Graph(filenameOrder);

		TaskManager tm(csvTaskData);
		tm.Print();
		tm.Graph(filenameTask);
		cout << "Item integrity check\n";
		//try {
			im.IntegrityCheck(tm);
		//}
		//catch (string& e) {
		//	cerr << e << "\n";
		//}

		//cout << "Order integrity check \n";
		//try {
			om.IntegrityCheck(im);
		//}
		//catch (string& e) {
		//	cerr << e << "\n";
	//	}

		//cout << "Task integrity check\n";
		//try {
			tm.IntegrityCheck();
		//}
		//catch (string& e) {
		//	cerr << e << "\n";
		//}

	
	} catch (const string& e){
		cerr << e << "\n";
	}
}