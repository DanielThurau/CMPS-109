/* Interface.h */
#include "../common.h"
#include "../base/KnowledgeBase.h"
#include "../base/RuleBase.h"
#include "../inference/Inference.h"
#include "../load/Load.h"
#ifndef INTERFACE_H
#define INTERFACE_H

using namespace std;

class Interface {
	private:
		KnowledgeBase * KB;
		RuleBase * RB;
	public: 
		/* Basic constructor. Calls constructor on KB and RB */
		Interface();
		/* May be removed, paramatarized constructor.  Assigns ptrs */
		Interface(KnowledgeBase * p_KB, RuleBase * p_RB);
		/* commandLine().  Session for user, loops after each commnd */
		void commandLine();
		/* executecommand, given a 2d vector of strings, execute a set of
		commands depending on what is passed */
		bool executeCommand(std::vector<std::vector<std::string>> p_command);
		/* PArse SEG? */
		std::vector<std::string> parseSeg(std::string target);
		/* parse takes in a string and returns a 2d vector of strings */
		bool parse(std::string p_statment);
		/* destructor for interface */
		virtual ~Interface();
};
#endif

