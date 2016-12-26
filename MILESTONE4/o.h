#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

#include "i.h"

class Order {
	string orderCustomerName, orderProductName;
	vector<string> itemList;
public:
	Order(vector<string> row);
	void Print();
	void Graph(fstream&);
	string& getCustomer() { return orderCustomerName; }
	string& getProduct() { return orderProductName; }
	size_t size() { return itemList.size(); }
	string& getItem(size_t i) { return itemList[i]; }
};

class OrderManager {
	vector< Order > orderList;
public:
	OrderManager(vector < vector<string > >& csvData);
	void Print();
	void Graph(string& filename);
	void IntegrityCheck(ItemManager& im);
};
