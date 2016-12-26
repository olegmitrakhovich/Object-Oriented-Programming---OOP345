#pragma once

#include "o.h"

class Job : public Order {
	vector <bool> installed;
public:
	Job() {}
	Job(Order *o) : Order(*o) {
		installed.resize(size());

		for (size_t i = 0; i < size(); i++)
			installed[i] = false;
	}

	bool Installed(size_t i) { return installed[i]; }
	void Installed(size_t i, bool value) { installed[i] = value; }
};