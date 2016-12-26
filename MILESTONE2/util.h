#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// put '|' for pipe symbol

using namespace std;

void Trim(string& f);

void csvPrint(vector < vector<string> > csvData);

void csvReader(string& filename, char delim, vector<vector<string> >& csvData);

