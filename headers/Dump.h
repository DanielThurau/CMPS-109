/* dump.h */

#include "../common.h"
#include "../streamer/Streamer.h"
#ifndef DUMP_H
#define DUMP_H

class Interface;

class Dump: public Streamer {
	public:
		// Constructor using string and interface pointer
		Dump(std::string p_pathName, Interface * p_sri);

		// Process that performs all of file dump
		bool process();

		// Deconstructor
		~Dump();

};
#endif