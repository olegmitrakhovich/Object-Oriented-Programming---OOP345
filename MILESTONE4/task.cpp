#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"
// put '|' for pipe symbol

using namespace std;

class Task {
	string taskName, taskSlots, taskPass, taskFail;
public:
	Task(vector<string>& row) : taskSlots("1") {
		switch (row.size()) {
		case 4:
			if (validTaskName(row[3])) {
				taskFail = row[3];
			}
			else {
				throw string("expected fail task name, found [") + row[3] + "]";
			}
		case 3:
			if (validTaskName(row[2])) {
				taskPass = row[2];
			}
			else {
				throw string("expected fail task name, found [") + row[2] + "]";
			}
		case 2:
			if (validSlotName(row[1])) {
				taskSlots = row[1];
			}
			else {
				throw string("expected fail task name, found [") + row[2] + "]";
			}
		case 1:
			if (validTaskName(row[0])) {
				taskName = row[0];
			}
			else {
				throw string("expected fail task name, found [") + row[0] + "]";
			}
			break;

		default:
			throw string("expected 1,2,3, or 4 fields, found -") + to_string(row.size());
		}
	}

	~Task() {}

	void Print() {
		cout << "[" << taskName << "]" 
			 << "[" << taskSlots << "] " 
			<< " [" << taskPass << "] " 
			<< " [" << taskFail << "]\n";
	}

	void Graph(fstream& os) {
		if (!taskFail.empty()) {
			os << '"' << taskName << '"' 
			   << "->" 
			   << '"' << taskFail << '"' 
			   << "[color = red];\n";
		}

		if (!taskPass.empty()) {
			os << '"' << taskName << '"' 
			   << "->" << '"' << taskPass << '"' 
			   << "[color=green];\n";
		}

		if (taskFail.empty() && taskPass.empty()) {
			os << '"' << taskName << '"' << ";\n";
		}
	}

};

class TaskManager {
	vector <Task> taskList;
public:
	TaskManager(vector < vector<string> >& csvdata) 
	{
		int lineNumber = 0;
		for (auto row : csvdata) {
			try {
				lineNumber++;
				taskList.push_back(move(Task(row))); //here
			}
			catch (string& e) {
				cerr << "problem with line" << lineNumber << ":" << e << "\n";
			}
		}
	}

	void Print() {
		int lineNumber = 0;
		for (auto t : taskList) {
			lineNumber++;
			cout << lineNumber << ":";
			t.Print();
		}
	}

	void Graph(string& filename) {
		fstream os(filename + ".gv", ios::out);
		if (os.is_open()) {
			os << "digraph taskGraph {\n";
			for (auto t : taskList) {
				t.Graph(os);
			}
			os << "}\n";
			os.close();
			string cmd;

			//#ifdef _MSVC
			//	cmd += "C:\\\"Program File(x86)\"\\Graphviz2.38\\bin\\dot.exe -tpng"
			//#else
			//cmd = "dot";
			//#endif

			cmd += string("dot -Tpng") + filename + ".gv >" + filename + ".gv.png";
			//	cmd += filename + ">" + filename + ".png";
			cout << "running" << cmd << "\n";
			system(cmd.c_str());
		}
	}

};


int main(int argc, char* argv[]) {
	try {
		if (argc != 3) {
			throw string("usage:") + argv[0] + string(": file.csv delimeter-char");
		}
		string filename = string(argv[1]); //1st arg
		char delimiter = argv[2][0]; //1st char of second arg

		vector< vector <string> > csvTaskData;
		csvRead(filename, delimiter, csvTaskData);

		//csvPrint(csvTaskData);

		TaskManager tm(csvTaskData);
		tm.Print();
		tm.Graph(filename);
	}catch ( const string& e) {
		cerr << e << "\n";
	}

	return 0;
}