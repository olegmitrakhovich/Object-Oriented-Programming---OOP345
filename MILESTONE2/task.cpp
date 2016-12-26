#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"
// put '|' for pipe symbol

using namespace std;

bool validSlotname(string& t)
{
	if (t.empty()) return false;

	for (auto c : t) {
		if (!(isalnum(c) || c == ' ' || c =='_')) { // if letter not (alphanumeric), space or underscore
			return false;
		}
	}

	return true;
}

bool validTaskname(string& t)
{
	for (auto c : t) {
		if (!(isdigit(c) )) { // if not number
			return false;
		}
	}
	return true;
}

class Task {
	string taskName, taskSlots, taskaccept, taskFail;
public:
	Task(vector<string>& row) : taskSlots("1") {
		switch (row.size()) {
		case 4:
			if (validTaskname(row[3]))
				taskFail = row[3];
			else
				throw string("expected fail task name, found [") + row[3] + "]";
		case 3:
			if (validTaskname(row[3])) {
				taskaccept = row[2];
			}
			else {
				throw string("expected fail task name, found [") + row[2] + "]";
			}
		case 2:
			if (validSlotname(row[1])) {
				taskSlots = row[1];
			}
			else {
				throw string("expected fail task slot, found [") + row[1] + "]";
			}
		case 1:
			if (validTaskname(row[0])) {
				taskName = row[0];
			}
			else {
				throw string("expected fail task name, found [") + row[0] + "]";
				break;
			}
		default:
			throw string("expected 1,2,3, or 4 fields, found -") + to_string(row.size());
		}
	}

	~Task() {

	}

	void TaskPrint() {
		cout << "<" << taskName << ">" << " <" << taskSlots << "> " << "<" << taskaccept << "> " << " <" << taskFail << ">\n";
	}

	void TaskGraph(fstream& os){
		if (!taskFail.empty()) {
			os << '"' << taskName << '"' << "->" << '"' << taskFail << '"' << ";\n";
		}

		if (!taskaccept.empty()) {
			os << '"' << taskName << '"' << "->" << '"' << taskaccept << '"' << ";\n";
		}

		if (taskFail.empty() && taskaccept.empty()) {
			os << '"' << taskName << '"' << ";\n";
		}
	}

};

class TaskManager {
	vector <Task> taskList;
public:
	TaskManager(vector < vector<string> >& csvdata) {
		int lineNumber = 0;
		cout << "HELLO4";
		for (auto row : csvdata) {
			try {
				lineNumber++;
				cout << "HELLO5";
				taskList.push_back(move(Task(row)));
				cout << "HELLO6";
			}
			catch (string& e) {
				cerr << "problem with line" << lineNumber << ":" << e << "\n";
			}
		}
		cout << "HELLO6";
	}

	void TaskPrint() {
		cout << "HELLO2";
		int lineNumber = 0;
		for (auto t : taskList) {
			lineNumber++;
			cout << "Task " << lineNumber << ":";
			t.TaskPrint();
		}
	}

	void TaskGraph(string& filename) {
		cout << "HELLO";
		fstream os(filename + ".gv", ios::out);
		os << "diagraph taskGraph {\n";
		for (auto t : taskList){
			t.TaskGraph(os);
		}
		os << "}\n";
		os.close();
		string cmd;
#ifdef _MSVC
	cmd += "C:\Program File(x86)\Graphviz2.38\bin\dot.exe"
#else
cmd = "dot";
#endif
		cmd += string("dot - Tpng") + filename + ".gv >" + filename + ".gv.png";
		cout << "running" << cmd << "\n";
		//system(cmd.c_str());
	}

	~TaskManager() {

	}

};


int main(int argc, char* argv[]) {
	try {
		if (argc != 3)
			throw string("usage:") + argv[0] + "file.csv delimeter-char";
		string filename = argv[1]; //1st arg
		char delim = argv[2][0]; //1st char of second arg

		vector< vector <string> > csvTaskData;
		cout << "here";
		csvReader(filename, delim, csvTaskData);
		
		csvPrint(csvTaskData);

		TaskManager tm(csvTaskData);
		tm.TaskPrint();
		tm.TaskGraph(filename);
	}
	catch (string& e) {
		cerr << e << "\n";
	}

	return 0;
}