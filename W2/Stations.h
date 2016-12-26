#pragma once
#include "Station.h"

namespace w2 {

	class Stations {
		char* file;
		int num_stations;
		Station* ptr;
	public:
		Stations(char*);
		~Stations();
		void update() const;
		void restock() const;
		void report() const;
	};

}
/*
public:
stations(char* f) : file(f){
}
*/