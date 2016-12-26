//#ifndef C_STRING_H
//#define C_STRING_H

#pragma once
#define MAX 3
#include <cstring>
#include <iostream>

namespace w1 {

	class CString {
		char str[MAX + 1];
	public:
		CString(char*);
		void display(std::ostream&) const;
	};

	std::ostream& operator<<(std::ostream&, const CString);

}

//#endif
