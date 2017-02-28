/* dump.h */

#include "../common.h"
#include "../streamer/Streamer.h"
#ifndef DUMP_H
#define DUMP_H

<<<<<<< HEAD

class Dump: public Streamer {
	public:
		Dump(std::string p_pathName, KnowledgeBase * KB, RuleBase * RB);
=======
class Interface;

class Dump: public Streamer {
	public:
		Dump(std::string p_pathName, Interface * p_sri);
>>>>>>> Dan

		bool process();

		~Dump();

};
<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> Dan
