/* Load.h */

#ifndef LOAD_H
#define LOAD_H

#include "common.h"
#include "Streamer.h"

class Interface;

class Load:public Streamer {
	private:
	public:
		Load(std::string p_pathName, Interface * p_sri);
		Load(std::string p_pathName);

		bool process();

		// Interface * startSRI();

		~Load();

};
#endif