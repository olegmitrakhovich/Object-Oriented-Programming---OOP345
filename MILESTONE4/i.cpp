#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

#include "i.h"

Item* ItemManager::FindItem(std::string& name) {
	for (size_t i = 0; itemList.size(); i++) {
		if (itemList[i].getItemName() == name)
			return &itemList[i];
 }
	return nullptr;
}

Item::Item(vector<string> row)
{
	switch (row.size()) {
	case 5:
		itemDescription = row[4];
	case 4:
		if (validItemSequence(row[3]))
			itemSequence = row[3];
		else
			throw string("expected sequence, found [") + row[3] + "]";
	//case 3:
		if (validTaskName(row[2]))
			itemRemoverTask = row[2];
		else
			throw string("expected fail item name, found [") + row[2] + "]";
	//case 2:
		if (validTaskName(row[1]))
			itemInstallerTask = row[1];
		else
			throw string("expected fail item name, found [") + row[1] + "]";
	//case 1:
		if (validItemName(row[0]))
			itemName = row[0];
		else
			throw string("expected fail item name, found [") + row[0] + "]";
		break;
	default:
		throw string("expected 4 or 5 fields, found -") + to_string(row.size());
	}
}

void Item::Print()
{
	cout << "[" << itemName << "]"
		<< "[" << itemInstallerTask << "]"
		<< "[" << itemRemoverTask << "]"
		<< "[" << itemSequence << "]"
		<< "[" << itemDescription << "]\n";
}

void Item::Graph(fstream& os)
{
	os << '"' << "Item\n" << itemName << '"'
		<< "->"
		<< '"' << "Installer\n" << itemInstallerTask << '"'
		<< "[color=green];\n";

	os << '"' << "Item\n" << itemName << '"'
		<< "->" << '"' << "Remover\n" << itemRemoverTask << '"'
		<< "[color=red];\n";
}

ItemManager::ItemManager(vector < vector<string > > & csvData) {
	int lineNumber = 0;
	for (auto row : csvData) {
		try {
			lineNumber++;
			itemList.push_back(move(Item(row)));
		}
		catch (string& e) {
			cerr << "Problem with line " << lineNumber << "; " << e << "\n";
		}
	}
}

void ItemManager::Print() {
	int lineNumber = 0;
	for (auto t : itemList) {
		lineNumber++;
		cout << lineNumber << ": ";
		t.Print();
	}
}

void ItemManager::Graph(string& filename)
{
	fstream os(filename + ".gv", ios::out);
	if (os.is_open()) {

		os << "digraph itemgraph {\n";
		for (auto t : itemList) {
			t.Graph(os);
		}
		os << "}\n";
		os.close();

		string cmd;
		cmd = "dot";
		cmd += string(" -Tpng ") + filename + ".gv >" + filename + ".gv.png";
		//string cmd = "C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng " + filename + ".gv > " + filename + ".png";
		cout << "running" << cmd << "\n";
		system(cmd.c_str());
	}
}

void ItemManager::IntegrityCheck(TaskManager& tm) {
	for (auto i : itemList) {
		if (tm.FindTask(i.getItemInstallerTask()) == nullptr) {
			throw std::string("Item '") + i.getItemName() + "' references installer task '" + i.getItemInstallerTask() + "' but it does not exist!";
		}

		if (tm.FindTask(i.getItemRemoverTask()) == nullptr) {
			throw std::string("Item ") + i.getItemName() + "references remover task " + i.getItemRemoverTask() + " but it does not exist!";
		}

	}
}
