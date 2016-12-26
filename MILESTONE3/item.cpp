#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;


class item {
	string itemName, itemInstaller, itemRemover, itemSequence, itemDescription;
public:
	item(vector <string> & row) {
		switch (row.size())
		{
		case 5:
			itemDescription = row[4];
		case 4:
			if (ValidItemSequence(row[3]))
			{
				itemSequence = row[3];
			}
			else
			{
				throw string("Expected a sequence number, found >") + row[3] + "<";
			}

			//case 3:
			if (ValidTaskName(row[2]))
			{
				itemRemover = row[2];
			}
			else
			{
				throw string("Expected remover task name, found >") + row[2] + "<";
			}
			//case 2:
			if (ValidTaskName(row[1]))
			{
				itemInstaller = row[1];
			}
			else
			{
				throw string("Expected installer task name, found >") + row[1] + "<";
			}
			//case 1:
			if (ValidItemName(row[0]))
			{
				itemName = row[0];
			}
			else
			{
				throw string("Expected item name, found >") + row[0] + "<";
			}

			break;
		default:
			throw string("Expected 1,2,3 or 4 fields, but found ") + to_string(row.size());
		}
	}
	void Print() {
		cout << "[" << itemName << "] "
			<< "[" << itemInstaller << "] "
			<< "[" << itemRemover << "] "
			<< "[" << itemSequence << "] "
			<< "[" << itemDescription << "] "
			<< "\n";
	}
	void Graph(fstream& os) {
		os << '"' << "Item\n" << itemName << '"'
			<< "->"
			<< '"' << "Installer\n" << itemInstaller << '"' << "[color=green]" << ";\n";

		os << '"' << "Item\n" << itemName << '"'
			<< "->"
			<< '"' << "Remover\n" << itemRemover << '"' << "[color=red]" << ";\n";
	}

};

class itemManager {
	vector <item> itemList;
public:
	itemManager(vector <vector<string>>& csvitem) {
		int lineNumber = 0;
		for (auto &row : csvitem) {
			try {
				lineNumber++;
				itemList.push_back(move(item(row)));
			}
			catch (const string& e) {
				cerr << "Error on line " << lineNumber << ":" << e << "\n";
			}
		}
	}
	void Print() {
		int lineNumber = 0;
		for (auto t : itemList) {
			lineNumber++;
			cout << lineNumber << ": ";
			t.Print();
		}
	}
	void Graph(string& filename) {
		fstream os(filename, ios::out | ios::trunc);
		if (os.is_open()) {
			os << "digraph item {\n";
			for (auto t : itemList) {
				t.Graph(os);
			}
			os << "}\n";
			os.close();


			string cmd = "dot -Tpng " + filename + " > " + filename + ".png";

			//string cmd = "C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng " + filename + " > " + filename + ".png";
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
		itemManager im(csvData);
		im.Print();
		string graphLine = filename + ".gv";
		im.Graph(graphLine);
	}
	catch (const string& e) {
		cerr << e << "\n";
	}
}
