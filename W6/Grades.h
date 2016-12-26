
#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Grades {
	int* studentnumber;
	float* grade;
	int count;
public:
	Grades(char* file);
	template<typename letter>
	void displayGrades(std::ostream& os, letter LETTER) const {
		for (int i = 0; i < count; i++) {
			os << studentnumber[i] << " " << grade[i] << " " << LETTER(grade[i]) << std::endl;
		}
	}
};
