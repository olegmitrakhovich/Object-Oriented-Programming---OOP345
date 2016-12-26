#include "Grades.h"

Grades::Grades(char* file) {
	try {
		std::fstream myfile(file);

		if (!myfile.is_open()) {
			throw 99;
		}

		std::string strings;


	//std::getline(myfile, strings, '\n');

	int i = 0;
	int size = 0;

	while (myfile) {
		std::string number;
		std::string mark;
		std::getline(myfile, number, ' ');
		std::getline(myfile, mark, '\n');
		size++;
	}

	count = size;

	studentnumber = new int[size];
	grade = new float[size];

	myfile.clear();
	myfile.seekg(0);

	while (myfile)
	{
		std::string number;
		std::string mark;
		std::getline(myfile, number, ' ');
		studentnumber[i] = atoi(number.c_str());
		std::getline(myfile, mark, '\n');
		grade[i] = atof(mark.c_str());
		i++;
	}

	} catch (int x) {
	std::cout << "FILE IS NOT FOUND ERROR " << x << std::endl;
	}

}


