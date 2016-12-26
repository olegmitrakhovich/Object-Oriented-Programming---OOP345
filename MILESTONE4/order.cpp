#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

class Order {
	string orderCustomerName, orderProductName;
	vector<string> itemList;
public:
	Order(vector<string> row)
	{
		if (row.size() < 3) {
			throw string("need at least 3 fields, found ") + to_string(row.size());
		}

		if (validOrderCustomerName(row[0]))
			orderCustomerName = row[0];
		else
			throw string("expected customer name, found [") + row[0] + "]";

		if (validOrderProductName(row[1]))
			orderProductName = row[1];
		else
			throw string("expected product name, found [") + row[1] + "]";

		for (size_t i = 2; i < row.size(); i++)
			if (validItemName(row[i]))
				itemList.push_back(row[i]);
			else
				throw string("expected item name, found [") + row[i] + "]";
	}

	void Print()
	{
		cout << "[" << orderCustomerName << "]"
			<< "[" << orderProductName << "] ";
		for (auto e : itemList)
			cout << "[" << e << "] ";
		cout << "\n";
	}

	void Graph(fstream& os)
	{
		for (auto e : itemList)
			os << '"' << orderCustomerName << "\n" << orderProductName << '"'
			<< "->"
			<< '"' << e << '"'
			<< "[color=blue];\n";
	}
};

class OrderManager {
	vector < Order > orderList;
public:
	OrderManager(vector <vector<string > > & csvData)
	{
		int lineNumber = 0;
		for (auto row : csvData) {
			try {
				lineNumber++;
				orderList.push_back(move(Order(row)));
			}
			catch (string& e) {
				cerr << "Problem with line " << lineNumber << ": " << e << "\n";
			}
		}
	}

	void Print()
	{
		int lineNumber = 0;
		for (auto t : orderList) {
			lineNumber++;
			cout << lineNumber << ": ";
			t.Print();
		}
	}

	void Graph(string& filename)
	{
		fstream os(filename + ".gv", ios::out);
		if (os.is_open()) {

			os << "digraph ordergraph { \n";
			for (auto t : orderList) {
				t.Graph(os);
			}
			os << "}\n";
			os.close();

			string cmd;
			cmd = string("dot -Tpng") + filename + ".gv >" + filename + ".gv.png";
			cout << "running " << cmd << "\n";
			system(cmd.c_str());
		}
	}
};

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
	} catch (const string& e){
		cerr << e << "\n";
	}
}