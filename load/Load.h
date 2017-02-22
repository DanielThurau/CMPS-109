/* Load.h */
#include "../common.h"
#include "../streamer/Streamer.h"

class Interface;

class Load:public Streamer {

	public:
		Load(std::string p_pathName, KnowledgeBase * KB, RuleBase * RB);
		Load(std::string p_pathName);

		bool process();

		Interface * startSri();

		~Load();

};