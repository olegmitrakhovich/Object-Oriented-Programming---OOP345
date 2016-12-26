#include "Text.h"
#include <fstream>
#include <algorithm>
#include <cstring>

using namespace w3;

void Text::display() const {
	std::cout << content;
}

Text::~Text() {
	delete[] content;
}

Text::Text(Text&& obj) {
	content = obj.content;
	file = obj.file;
	strings = obj.strings;
	obj.content = nullptr;
	obj.file = " ";
	obj.strings = " ";
}

Text&& Text::operator=(Text&& obj) {
	if (&obj != this) {
		content = obj.content;
		file = obj.file;
		strings = obj.strings;
		obj.content = nullptr;
		obj.file = " ";
		obj.strings = " ";
	}
	return std::move(*this);
}

Text::Text() {
	file = " ";
	strings = " ";
	content = nullptr;
}

Text& Text::operator=(const Text& source) {
	if (this != &source) {
		strings = source.strings;
		file = source.file;
		delete [] content;
		
		if (source.content != nullptr) {
			content = new char[source.size()];
			strcpy(content, source.content);
		}
		else {
			content = nullptr;
		}

	}
	return *this;
}

Text::Text(std::string input) {
	
	file = input;
	std::fstream myfile(file);

	if (!myfile.is_open()) {
		std::cout << "File is not found" << std::endl;
		myfile.clear();
		myfile.close();
		file = " ";
		strings = " ";
		exit(1);
		}else{
		
		size_t count = 0;
		std::getline(myfile, strings, '\0');
		
		count = strings.size();
		//std::cout << "count of characters: " << count;
	
		content = new char[count];
	        strcpy(content,strings.c_str());
		
		myfile.close();
		myfile.clear();
	
	}

}

size_t Text::size() const {
	
	return strings.size();

}

Text::Text(const Text& obj){

	content = nullptr;
	*this = obj;

}
