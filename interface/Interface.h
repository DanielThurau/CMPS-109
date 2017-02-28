/* Interface.h */
#include "../common.h"
#include "../base/KnowledgeBase.h"
#include "../base/RuleBase.h"
#include "../inference/Inference.h"
// #include "../load/Load.h"
// #include "../streamer/Streamer.h"
#ifndef INTERFACE_H
#define INTERFACE_H



class Load;
class Dump;
// class Streamer;

using namespace std;

class Interface {
	public: 
		KnowledgeBase * KB;
		RuleBase * RB;
		Interface();
		Interface(KnowledgeBase * p_KB, RuleBase * p_RB);
		void commandLine();
		bool executeCommand(std::vector<std::vector<std::string>>
								p_command);
		std::vector<std::string> parseSeg(std::string target);
		bool parse(std::string 
								p_statment);
		virtual ~Interface();
};
#endif

