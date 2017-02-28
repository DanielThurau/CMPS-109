/* dump.h */

#include "../common.h"
#include "../streamer/Streamer.h"
#ifndef DUMP_H
#define DUMP_H

class Interface;

class Dump: public Streamer {
	public:
		Dump(std::string p_pathName, Interface * p_sri);

		bool process();

		~Dump();

};
#endif