#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"
// put '|' for pipe symbol

using namespace std;

void Trim(string& f) {
	while (!f.empty() && f[0] == ' ') { //delete leading space
		f.erase(0, 1);
	}

	while (!f.empty() && f[f.size() - 1] == ' ') // delete trailing spaces
		f.erase(f.size() - 1, 1);
}

void csvPrint(vector < vector<string> > csvData) {
	cout << "number of lines = " << csvData.size() << "\n";

	// print using indexes
	for (size_t row = 0; row < csvData.size(); row++) {
		cout << "row =" << row << " ";
		for (size_t column = 0; column < csvData[row].size(); column++) {
			cout << "'" << csvData[row][column] << "' ";
			//cout << "\n";
		}
		cout << "\n";
	}

	// print using iterators
	for (auto rowIt = csvData.begin(); rowIt != csvData.end(); rowIt++) {
		for (auto columnIt = rowIt->begin(); columnIt != rowIt->end(); columnIt++) {
			cout << "'" << *columnIt << "\n";
		}
		cout << "\n";
	}

	// print using range-based for    //ON THE EXAM
	for (auto row : csvData) {
		for (auto column : row) {
			cout << "'" << column << "'";
			//cout << "\n";
		}
		cout << "\n";
	}
}

void csvReader(string& filename, char delim, vector<vector<string> >& csvData) {
	fstream is(filename, ios::in);
	cout << "here";
	if (!is.is_open())
		throw string("cannot open file") + filename;

	string line;
	cout << "here";
	while (getline(is, line)) {
		cout << "here5";
		auto cr = line.find('\r');
		cout << "here6";
		if (cr != string::npos) 
			line.erase(cr);
			cout << "here7";
		cout << "here3";
		cout << "line ==>" << line << "<==\n";
		vector <string> fields;
		string field;
		size_t i = 0;
		while (i < line.size()) {
			if (line[i] != delim) {
				field += line[i];
			}
			else { // found delimeter
				Trim(field);
				fields.push_back(move(field)); // add field to our lost of fields
				//field.clear();
			}
			i++;
		} // end of processing line
		if (!field.empty()) {
			Trim(field);
			fields.push_back(move(field));
			//add line fields to csvData
			csvData.push_back(move(fields));
			//fields.clear();
		}
	}

	is.close();
	cout << "here2";
}


