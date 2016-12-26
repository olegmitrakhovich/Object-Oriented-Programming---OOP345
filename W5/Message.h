#pragma once
#include <iostream>


namespace w5 {

	class Message {
		std::string user, tweet, reply;
	public:
		Message();
		Message(std::ifstream& in, char c);
		bool empty() const;
		void display(std::ostream&) const;
	};

}