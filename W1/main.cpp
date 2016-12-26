#include "CString.h"
#include "process.h"
#include <iostream>


int main(int argc, char *argv[]) {
		std::cout << "Command Line : ";
                for (int arg = 0; arg < argc; arg++){
                std::cout << argv[arg] << " ";
                }

		std::cout << std::endl;

		if (argc > 1) {
		std::cout << "Maximum number of characters stored : " << MAX << std::endl;
		for (int i = 1; i < argc; i++) {
			process(argv[i]);
		}
		return 0;
	}
	else {
		std::cout << "Insufficent number of arguments(min 1)" << std::endl;
		return 1;
	}
}
