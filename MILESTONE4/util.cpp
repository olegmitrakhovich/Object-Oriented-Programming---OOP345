#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

// put '|' for pipe symbol

using namespace std;

bool validTaskName(string& t)
{
	if (t.empty()) {
		return false;
	}

	for (auto c : t) {
		if (!(isalnum(c) || c == ' ' || c == '_')) { // if letter not (alphanumeric), space or underscore
			return false;
		}
	}

	return true;
}

bool validSlotName(string& t)
{
	if (t.empty()) {
		return false;
	}

	for (auto c : t) {
		if (!(isalnum(c))) { // if not number
			return false;
		}
	}
	return true;
}

//not sure about these///////////////////////////////////////////////////////////
bool validItemName(string& t) {
	if (t.empty()) {
		return false;
	}

	for (auto c : t) {
		if (!(isalnum(c) || c == ' ' || c == '_')) { // if letter not (alphanumeric), space or underscore
			return false;
		}
	}

	return true;
}

bool validOrderCustomerName(string& t) {
	if (t.empty()) {
		return false;
	}

	for (auto c : t) {
		if (!(isalnum(c) || c == ' ' || c == '_')) { // if letter not (alphanumeric), space or underscore
			return false;
		}
	}

	return true;
}

bool validOrderProductName(string& t) {

	if (t.empty()) {
		return false;
	}

	for (auto c : t) {
		if (!(isalnum(c) || c == ' ' || c == '_')) { // if letter not (alphanumeric), space or underscore
			return false;
		}
	}

	return true;
}

bool validItemSequence(string& t) {
	
	if (t.empty()) return false;

	for (auto c : t) {
		if (!isdigit(c))
			return false;
	}

	return true;
}




////////////////////////////////////////////////////////////////////////////////



void Trim(string& f) {
	while (!f.empty() && f[0] == ' ') { //delete leading space
		f.erase(0, 1);
	}

	while (!f.empty() && f[f.size() - 1] == ' ') // delete trailing spaces
		f.erase((f.size() - 1), 1);
}

void csvPrint(vector < vector<string> > & csvData) {
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

void csvRead(string& filename, char delim, vector<vector<string> >& csvData) {
	fstream is(filename, ios::in);

	if (!is.is_open())
		throw string("cannot open file") + filename;

	string line;
	while (getline(is, line)) {
		auto cr = line.find('\r');
		if (cr != string::npos)
			line.erase(cr);

		//	cout << "line ==>" << line << "<==\n";
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
			fields.clear();
		}
	}

	is.close();
}
