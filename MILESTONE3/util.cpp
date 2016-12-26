#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

//vector <vector<string>>& csvData;

bool ValidItemName(string& t) {
	if (t.empty())
	{
		return false;
	}
	for (auto chr : t) {
		if (isspace(chr) || isalnum(chr) || chr == '_')
		{
			continue;
		}
		return false;
	}
	return true;
}

bool ValidItemSequence(string& t) {
	if (t.empty())
	{
		return false;
	}
	for (auto chr : t) {
		if (isdigit(chr))
		{
			continue;
		}
		return false;
	}
	return true;
}

bool ValidTaskName(string& t) {
	if (t.empty())
	{
		return false;
	}
	for (auto chr : t) {
		if (isspace(chr) || isalnum(chr) || chr == '_')
		{
			continue;
		}
		return false;
	}
	return true;
}

bool ValidTaskSlots(string& t) {
	if (t.empty())
	{
		return false;
	}
	for (auto chr : t) {
		if (isdigit(chr))
		{
			continue;
		}
		return false;
	}
	return true;
}

void trim(string& s)
{
	while (s.size() > 0 && s[0] == ' ') // Kill leading spaces
	{
		s.erase(0, 1);
	}
	while (s.size() > 0 && s[s.size() - 1] == ' ') // Kill trailing spaces
	{
		s.erase(s.size() - 1, 1);
	}
}

void csvPrint(vector <vector<string>>& csvData) {
	for (size_t row = 0; row < csvData.size(); row++)
	{
		cout << "row " << row << " ";
		cout << "(" << csvData[row].size() << " fields) ";
		for (size_t column = 0; column < csvData[row].size(); column++)
		{
			cout << "[" << csvData[row][column] << "] ";
		}
		cout << "\n";
	}
	cout << "\nRange Based for print\n";
	for (auto row : csvData) {
		cout << "(" << row.size() << " fields)";
		for (auto column : row) {
			cout << "<" << column << "> ";
		}
		cout << "\n";
	}
}
void csvread(string& filename, char delimiter, vector <vector<string>>& csvData) {
	fstream is(filename, ios::in);
	if (!is.is_open())
	{
		throw string("Cannot open file ") + filename;
	}
	string line;
	while (getline(is, line))
	{
		auto cr = line.find('\r');
		if (cr != string::npos)
		{
			line.erase(cr);
		}
		//cout << "line -->" << line << "<---\n";
		vector <string> fields;
		string field;
		size_t i = 0;

		while (i < line.size())
		{
			if (line[i] != delimiter) {
				field += line[i];
			}
			else
			{
				trim(field);
				fields.push_back(move(field));
			}
			i++;
		}
		// If last entry was not a delimiter?
		if (!field.empty())
		{
			trim(field);
			fields.push_back(move(field));
		}
		csvData.push_back(move(fields));
	}
	is.close();
}

bool ValidCusName(string& t) {
	if (t.empty())
	{
		return false;
	}
	for (auto chr : t) {
		if (isspace(chr) || isalnum(chr) || chr == '\'')
		{
			continue;
		}
		return false;
	}
	return true;
}
bool ValidProductName(string& t) {
	if (t.empty())
	{
		return false;
	}
	for (auto chr : t) {
		if (isspace(chr) || isalnum(chr) || chr == '\'' || chr == '#' || chr == '$')
		{
			continue;
		}
		return false;
	}
	return true;
}

bool ValidOrderName(string& t) {
	if (t.empty())
	{
		return false;
	}
	for (auto chr : t) {
		if (isspace(chr) || isalnum(chr) || chr == '_')
		{
			continue;
		}
		return false;
	}
	return true;
}

bool ValidOrderSequence(string& t) {
	if (t.empty())
	{
		return false;
	}
	for (auto chr : t) {
		if (isdigit(chr))
		{
			continue;
		}
		return false;
	}
	return true;
}
