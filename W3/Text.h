#pragma once
#include <string>
#include <iostream>

namespace w3 {

	class Text {
	std::string file;
	std::string strings;
	char* content;
	public:
		void display() const;
		Text();
		~Text();
		Text(const Text&);
		Text(std::string);
		size_t size() const;
		Text& operator=(const Text&);
		Text&& operator=(Text&& obj);
		Text(Text&& obj);
	};

}
