#pragma once

//ask to see this file

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void Trim(string& f);

void csvPrint(vector < vector< string > > & csvData);

void csvRead(string& filename, char delimiter, vector < vector<string > >& csvData);

bool validItemName(string& t);

bool validItemSequence(string& t);

bool validOrderCustomerName(string& t);

bool validOrderProductName(string& t);

bool validTaskName(string& t);

bool validSlotName(string& t);
