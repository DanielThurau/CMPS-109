/* Load.h */
#include "../common.h"
#include "../streamer/Streamer.h"
#ifndef LOAD_H
#define LOAD_H

class Interface;

class Load:public Streamer {
	private:
	public:
		Load(std::string p_pathName, Interface * p_sri);
		Load(std::string p_pathName);

		bool process();

		Interface * startSri();

		~Load();

};
#endif