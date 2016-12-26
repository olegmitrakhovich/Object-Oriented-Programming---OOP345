#include "Station.h"

void Station::set(const std::string& name , unsigned adultpass, unsigned studentpass) {
	
	station_name = name;
	s_pass = studentpass;
	a_pass = adultpass;

			
};

void Station::update(PassType type, int num)  {
	
	if (!type) {
		a_pass += num;
		
	}
	else {
		s_pass += num;
	
	};

};

unsigned Station::inStock(PassType type) const {
	

	if (!type) {
		return a_pass;
	}
	else {
		return s_pass;
	}

}; 

const std::string& Station::getName() const {
	return station_name;
};