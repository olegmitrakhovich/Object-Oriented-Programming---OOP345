#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

#include "i.h"
#include "o.h"
#include "t.h"

#include "machine.h"

class Factory {
	vector<Machine> machineList;
public:
	Factory()
	{

	}
	Factory(ItemManager& im, OrderManager& om, TaskManager& tm) {
		for (size_t count = 0; count < tm.size(); count++) {
			machineList.push_back(move(Machine(tm.getTask(count))));
		}

		int line = 0;

		auto FindMachine = [&](string n) -> Machine* {
			for (size_t i = 0; i < machineList.size(); i++)
				if (machineList[i].getTaskName() == n)
					return &machineList[i];
			return nullptr;
		};
		for (auto m : machineList) {
			string pass = m.getTaskPass();
			if (!pass.empty()) FindMachine(pass)->IncInComing();

			string fail = m.getTaskFail();
			if (!fail.empty()) FindMachine(fail)->IncInComing();
		}

		int source = -1;
		for (size_t m = 0; m < machineList.size(); m++) {
			cout << m << ": " << machineList[m].getTaskName();
			if (machineList[m].isSingleton()) {
				cout << "SINGLETON";
			}
			else {
				if (machineList[m].isSource()) {
					cout << "SOURCE";
					if (source == -1) {
						source = m;
					}
					else {
						throw string("Multiple sourcces. Fix data and re-submit!");
					}
				}
				if (machineList[m].isSink()) cout << "SINK";
			}
			cout << "\n";
		}
		cout << "Source is " << source << "\n";

		for (size_t o = 0; o < om.getSize(); o++) {
			machineList[source].AddJob(Job(om.getOrder(o)));
		}

		for (auto m : machineList) {
			cout << m.getTaskName() << " has " << m.inputQSize() << " jobs.\n";
		}

		for (auto &m : machineList) {
			m.Classify(im);
		}

		while (true) {
			bool AllDone = true;
			for (auto m : machineList) {
				if (m.inputQSize()) {
					AllDone = false;
					break;
				}
			}
			if (AllDone) {
				cout << "All done\n";
				break;
			}

			for (auto &m : machineList) {
				if (m.inputQSize() == 0) {
					continue;
				}

				Job job = m.getJob();

				cout << m.getTaskName() << "is looking at job"
					<< job.getCustomer() << "/"
					<< job.getProduct() << "\n";

				if (m.isSink()) {
					cout << "Job arrived at sink --- nithing to do. \n";
					cout << "job exiting system\n";
					continue;
				}

				bool didSomething = false;

				if (m.getInstaller()) {
					cout << "we are installer\n";

					for (size_t i = 0; i < job.size(); i++) {
						if (job.Installed(i))
							continue;

						string itemName = job.getItem(i);
						Item* itemPtr = im.FindItem(itemName);
						if (m.getTaskName() == itemPtr->getItemInstallerTask()) {
							job.Installed(i, true);
							didSomething = true;
							break;
						}
					}
				}
				if (m.getRemover()) {
					cout << "we are a remover\n";

					for (int i = job.size() - 1; i >= 0; i--) {
						if (!job.Installed(i))
							continue;

						string itemName = job.getItem(i);
						Item* itemPtr = im.FindItem(itemName);
						if (m.getTaskName() == itemPtr->getItemRemoverTask()) {
							job.Installed(i, false);
							didSomething = true;
							break;
						}
					}
				}

				auto MovePass = [&] {
					string pass = m.getTaskPass();
					cout << "moving job to pass machine " << pass << "\n";
					for (auto &m2 : machineList) {
						if (m2.getTaskName() == pass) {
							m2.AddJob(job);
							break;
						}
					}
				};

				auto MoveFail = [&] {
					string fail = m.getTaskFail();
					cout << "moving job to fail machine" << fail << "\n";
					for (auto &m2 : machineList) {
						if (m2.getTaskName() == fail) {
							m2.AddJob(job);
							break;
						}
					}
				};

				if (!didSomething) {
					MovePass();
					continue;
				}

				if (m.getTaskFail().empty()) {
					MovePass();
					continue;
				}

				if (rand() & 1) {
					MovePass();
					continue;
				}
				else {
					MoveFail();
					continue;
				}
			}
		}
		cout << "Simulation over\n";
	}
};

int main(int argc, char*argv[]) {
	try {
		if (argc != 5) {
			throw string("Usage ") + argv[0] + string(": item order taks (the 3 csv files) delimiter error");
		}

		string filenameItem = string(argv[1]);
		string filenameOrder = string(argv[2]);
		string filenameTask = string(argv[3]);
		char delimiter = argv[4][0];
		
		vector < vector< string > > csvItemData;
		vector < vector< string > > csvOrderData;
		vector < vector< string > > csvTaskData;

		csvRead(filenameItem, delimiter, csvItemData);
		csvRead(filenameOrder, delimiter, csvOrderData);
		csvRead(filenameTask, delimiter, csvTaskData);

		ItemManager im(csvItemData);
		im.Print();
		im.Graph(filenameItem);

		OrderManager om(csvOrderData);
		om.Print();
		om.Graph(filenameOrder);

		TaskManager tm(csvTaskData);
		tm.Print();
		tm.Graph(filenameTask);

		bool GoodToGo = true;
		cout << "Item integrity check\n";
		try {
			im.IntegrityCheck(tm);
		}
		catch (string& e) {
			GoodToGo = false;
			cerr << e << "\n";
		}

		cout << "Order integrity check\n";
		try {
			om.IntegrityCheck(im);
		}
		catch (string& e) {
			GoodToGo = false;
			cerr << e << "\n";
		}

		cout << "Track integrity check\n";
		try {
			tm.IntegrityCheck();
		}
		catch (string& e) {
			GoodToGo = false;
			cerr << e << "\n";
		}

		if (GoodToGo == false) {
			cerr << "**************************************************\n";
			cerr << "*       DATA HAS ERRORS. FIX AND TRY AGAIN!      *\n";
			cerr << "**************************************************\n";
			exit(1);
		}

		cout << "******************************************************\n";
		cout << "* DATA PASSED THE INTEGRITY CHECK AND IS GOOD TO GO!  *\n";
		cout << "*******************************************************\n";

		Factory factory(im, om, tm);
	}
	catch (const string& e) {
		cerr << e << "\n";
	}
}