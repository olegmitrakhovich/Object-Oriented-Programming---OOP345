#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

#include "t.h"

Task::Task(std::vector<std::string> row) : taskSlots("1") {
	switch (row.size()) {
	case 4:
		if (validTaskName(row[3]))
			taskFail = row[3];
		else
			throw std::string("expected fail task name, found [") + row[3] + "]";
	case 3:
		if (validTaskName(row[2]))
			taskPass = row[2];
		else
			throw std::string("expected fail task name, found [") + row[2] + "]";
	case 2:
		if (validSlotName(row[1]))
			taskSlots = row[1];
		else
			throw std::string("expected fail task name, found [") + row[2] + "]";
	case 1:
		if (validTaskName(row[0]))
			taskName = row[0];
		else
			throw std::string("expected fail taks name, found [") + row[0] + "]";
		break;
	default:
		throw std::string("expected 1,2,3, or 4 fields, found - ") + to_string(row.size());
	}
}

void Task::Print()
{
	cout << "[" << taskName << "] "
		<< "[" << taskSlots << "] "
		<< "[" << taskPass << "] "
		<< "[" << taskFail << "]\n";
}

void Task::Graph(fstream& os) {
	if (!taskFail.empty())
		os << '"' << taskName << '"'
		<< "->"
		<< '"' << taskFail << '"'
		<< "[color=red];\n";
	if (!taskPass.empty())
		os << '"' << taskName << '"' \
		<< "->" << '"' << taskPass << '"' \
		<< "[color=green];\n";
	if (taskFail.empty() && taskPass.empty())
		os << '"' << taskName << '"'
		<< ";\n";
}

TaskManager::TaskManager(std::vector < std::vector < std::string > > & csvData)
{
	int linenumber = 0;
	for (auto row : csvData) {
		try {
			linenumber++;
			taskList.push_back(move(Task(row)));
		}
		catch (std::string& e) {
			cerr << "Problem with line " << linenumber << "; " << e << "\n";
		}
	}
}

void TaskManager::Print()
{
	int linenumber = 0;
	for (auto t : taskList) {
		linenumber++;
		cout << linenumber << ": ";
		t.Print();
	}
}

void TaskManager::Graph(std::string& filename)
{
	fstream os(filename + ".gv", ios::out);
	if (os.is_open()) {

		os << "digraph taskgraph {\n";
		for (auto t : taskList) {
			t.Graph(os);
		}

		os << "}\n";
		os.close();

		std::string cmd;

		//cmd = "C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe"

		cmd = "dot";
		cmd += std::string(" -Tpng ") + filename + ".gv >" + filename + ".gv.png";
		cout << "running" << cmd << "\n";
		system(cmd.c_str());
	}
}

Task* TaskManager::FindTask(std::string& name)
{
	for (size_t t = 0; t < taskList.size(); t++) {
		if (taskList[t].getTaskName() == name)
			return &taskList[t];
	}
	return nullptr;
}

void TaskManager::IntegrityCheck()
{
	for (auto t : taskList) {
		if (!t.getTaskPass().empty() && FindTask(t.getTaskPass()) == nullptr) {
			throw std::string("Task '") + t.getTaskName() + "' references Pass tasl '" + t.getTaskPass() + "'but it does not exist";
		}
		if (!t.getTaskFail().empty() && FindTask(t.getTaskFail()) == nullptr) {
			throw std::string("Task '") + t.getTaskName() + "' references Fail task '" + t.getTaskFail() + "' but it does not exist'";
		}
	}
}
