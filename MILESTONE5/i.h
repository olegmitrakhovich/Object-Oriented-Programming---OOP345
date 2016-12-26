#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

#include "t.h"


///code missing

class Item {
	string itemDescription, itemSequence, itemRemoverTask, itemName, itemInstallerTask;
public:
	Item(vector<string> row);
	void Print();
	void Graph(fstream&);
	std::string& getItemName() { return itemName; }
	std::string& getItemRemoverTask() { return itemRemoverTask; }
	std::string& getItemInstallerTask() { return itemInstallerTask; }
};

//code missing

class ItemManager {
	vector< Item > itemList;
public:
	ItemManager(vector <vector <string> >& csvData);
	void Print();
	void Graph(string& filename);
	Item* FindItem(std::string& name);
	void IntegrityCheck(TaskManager& tm);

	size_t getSize() { return itemList.size(); }
	Item* getItem(size_t i) { return &itemList[i]; }
};
