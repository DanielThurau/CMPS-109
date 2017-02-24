/* Load.h */
#include "../common.h"
#include "../streamer/Streamer.h"
#ifndef LOAD_H
#define LOAD_H

class Interface;

class Load:public Streamer {
	private:
		std::vector<std::string> parseSeg(std::string target);
	public:
		Load(std::string p_pathName, KnowledgeBase * KB, RuleBase * RB);
		Load(std::string p_pathName);

		bool process();

		Interface * startSri();

		~Load();

};
#endif
