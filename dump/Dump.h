/* dump.h */

#include "../common.h"
#include "../streamer/Streamer.h"
#ifndef DUMP_H
#define DUMP_H


class Dump: public Streamer {
	public:
		Dump(std::string p_pathName, KnowledgeBase * KB, RuleBase * RB);

		bool process();

		~Dump();

};
#endif
