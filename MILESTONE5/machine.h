#pragma once

#include <queue>

#include "t.h"
#include "job.h"

class Machine : public Task {
	int inComing;
	std::queue< Job > inputQ;

	bool bInstaller;
	bool bRemover;
public:
	Machine() : inComing(0) {
		
	}

	Machine(Task* t) : Task(*t), inComing(0) {

	}

	void IncInComing()
	{
		inComing++;
	}

	bool isSource() { return inComing == 0; }
	bool isSink() { return getTaskPass().empty(); }
	bool isSingleton() { return isSource() && isSink(); }

	void AddJob(Job job) { inputQ.push(move(job)); }

	size_t inputQSize() { return inputQ.size(); }

	Job getJob() {
		cout << "getJob: " << inputQSize() << "\n";
		Job job = move(inputQ.front());
		inputQ.pop();
		cout << "get Job after pop: " << inputQSize() << "\n";
		return job;
	}

	void Classify(ItemManager& im) {
		bInstaller = false;
		bRemover = false;
		for (size_t i = 0; i < im.getSize(); i++) {
			if (getTaskName() == im.getItem(i)->getItemInstallerTask())
				bInstaller = true;
			if (getTaskName() == im.getItem(i)->getItemRemoverTask())
				bRemover = true;
		}
		if (bInstaller) cout << getTaskName() << "is an installer\n";
		if (bRemover) cout << getTaskName() << "is a remover\n";
	}

	bool getInstaller() { return bInstaller;  }
	bool getRemover() { return bRemover; }
};
