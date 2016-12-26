#include "process.h"
#include "CString.h"
#include <iostream>


void process(char* string) {
	w1::CString obj(string);
	std::cout << obj;
};
