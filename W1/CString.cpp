
#include "CString.h"
#include <cstring>

using namespace w1;

	CString::CString(char* input) {
		if (strlen(input) != 0) {
		strncpy(str, input, MAX);
		str[MAX] = '\0';	
	}
		else {
			str[0] = '\0';
		}
	};

	void CString::display(std::ostream& os) const {
		os << str << std::endl;
	};

		

		std::ostream& w1::operator<<(std::ostream& os, const CString obj) {
			static int count = 0;
			os << count << ":";
			obj.display(os);
			count++;
			return os;
		};



