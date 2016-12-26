#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;



class order {
	string orderCustomer, orderProduct;
	vector<string> itemsOrdered;
public:
	//order(): orderSlots("1") {}
	order(vector <string> & row) {
		if (row.size() < 3) {
			throw string("Expected 3 or more, found ") + to_string(row.size());
		}
		if (ValidCusName(row[0])) {
			orderCustomer = row[0];
		}
		else
		{
			throw string("expected customer name, found [") + row[0] + "]";
		}
		if (ValidProductName(row[1])) {
			orderProduct = row[1];
		}
		else
		{
			throw string("expected product name, found [") + row[0] + "]";
		}

		for (size_t i = 2; i < row.size(); i++) {
			if (ValidItemName(row[i]))
			{
				itemsOrdered.push_back(move(row[i]));
			}
			else
			{
				throw string("expected item name, found [") + row[i] + "]";
			}
		}


	}
	void Print() {
		cout << "[" << orderCustomer << "] "
			<< "[" << orderProduct << "] "
			<< "\n";
		for (auto e : itemsOrdered) {
			cout << "[" << e << "] ";
		}
		cout << "\n";
	}
	void Graph(fstream& os) {
		for (auto e : itemsOrdered) {
			os << '"' << orderCustomer << "\n" << orderProduct << '"'
				<< "->"
				<< '"' << e << '"' << "[color=blue]" << ";\n";
		}
	}

};

class orderManager {
	vector <order> orderList;
public:
	orderManager(vector <vector<string>>& csvorder) {
		int lineNumber = 0;
		for (auto &row : csvorder) {
			try {
				lineNumber++;
				orderList.push_back(move(order(row)));
			}
			catch (const string& e) {
				cerr << "Error on line " << lineNumber << ":" << e << "\n";
			}
		}
	}
	void Print() {
		int lineNumber = 0;
		for (auto t : orderList) {
			lineNumber++;
			cout << lineNumber << ": ";
			t.Print();
		}
	}
	void Graph(string& filename) {
		fstream os(filename, ios::out | ios::trunc);
		if (os.is_open()) {
			os << "digraph order {\n";
			for (auto t : orderList) {
				t.Graph(os);
			}
			os << "}\n";
			os.close();
			  
			 string cmd = "dot -Tpng " + filename + " > " + filename + ".png";
			
			// windows string cmd = "C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng " + filename + " > " + filename + ".png";
			cout << "running -->" << cmd << "\n";
			cout << "command returned " << system(cmd.c_str()) << " (zero is good)\n";
		}
	}
};


int main(int argc, char* argv[]) {
	try {
		if (argc != 3) {
			throw string("Usage ") + argv[0] + string(" filename delimiter-char");
		}
		string filename = argv[1]; // First arg is file name
		char delimiter = argv[2][0]; // Second arg, 1st char is delimiter

		vector <vector<string>> csvData;
		csvread(filename, delimiter, csvData);

		//csvPrint(csvData);
		orderManager om(csvData);
		om.Print();
		string graphLine = filename + ".gv";
		om.Graph(graphLine);
	}
	catch (const string& e) {
		cerr << e << "\n";
	}
}
