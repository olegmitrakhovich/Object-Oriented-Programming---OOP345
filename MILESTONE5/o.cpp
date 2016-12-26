#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

#include "o.h"

Order::Order(vector<string> row)
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

void Order::Print() {
	cout << "[" << orderCustomerName << "]"
		<< "[" << orderProductName << "]";
	for (auto e : itemList)
		cout << "[" << e << "]";
	cout << "\n";
}

void Order::Graph(fstream& os)
{
	for (auto e : itemList)
		os << '"' << orderCustomerName << "\n" << orderProductName << '"'
		<< "->"
		<< '"' << e << '"'
		<< "[color=blue];\n";
}

OrderManager::OrderManager(vector < vector<string > > & csvData)
{
	int linenumber = 0;
	for (auto row : csvData) {
		try {
			linenumber++;
			orderList.push_back(move(Order(row)));
		}
		catch (string e) {
			cerr << "Problem with line" << linenumber << ": " << e << "\n";
		}
	}
}

void OrderManager::Print()
{
	int linenumber = 0;
	for (auto t : orderList) {
		linenumber++;
		cout << linenumber << ": ";
		t.Print();
	}
}

void OrderManager::Graph(string& filename)
{
	fstream os(filename + ".gv", ios::out);
	if (os.is_open()) {

		os << "digraph ordergraph {\n";
		for (auto o : orderList) {
			o.Graph(os);
		}
		os << "}\n";
		os.close();

		string cmd;

		//cmd = "C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe";

		cmd = "dot";
		cmd += string(" -Tpng ") + filename + ".gv >" + filename + ".gv.png";
		cout << "running " << cmd << "\n";
		system(cmd.c_str());
	}
}

void OrderManager::IntegrityCheck(ItemManager& im)
{
	for (auto o : orderList) {
		for (size_t count = 0; count < o.size(); count++) {
			if (im.FindItem(o.getItem(count)) == nullptr) {
				throw std::string("Order '") + o.getCustomer() + "/" + o.getProduct() +
					"' references item '" + o.getItem(count) + "' but it does not exist!";
			}
		}
	}
}