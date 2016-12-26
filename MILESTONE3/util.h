#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
void trim(string& s);
void csvPrint(vector <vector<string>>& csvData);
void csvread(string& filename, char delimiter, vector <vector<string>>& csvData);
bool ValidTaskName(string& t);
bool ValidTaskSlots(string& t);
bool ValidItemName(string& t);
bool ValidItemSequence(string& t);
bool ValidCusName(string& t);
bool ValidProductName(string& t);
bool ValidOrderName(string& t);
bool ValidOrderSequence(string& t);