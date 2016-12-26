#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

class Task {
	std::string taskName, taskSlots, taskPass, taskFail;
public:
	Task() {}
	Task(std::vector<std::string> row);
	void Print();
	void Graph(std::fstream& os);
	std::string& getTaskName() { return taskName; }
	std::string& getTaskPass() { return taskPass; }
	std::string& getTaskFail() { return taskFail; }
};

class TaskManager {
	std::vector < Task > taskList;
public: 
	TaskManager(std::vector < std::vector < std::string > >& csvData);
	void Print();
	void Graph(std::string& filename);
	Task* FindTask(std::string& name);
	void IntegrityCheck();
	size_t size() { return taskList.size(); }
	Task* getTask(size_t t) { return &taskList[t]; }
};

