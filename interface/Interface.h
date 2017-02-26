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
		Interface();
		Interface(KnowledgeBase * p_KB, RuleBase * p_RB);
		void commandLine();
		bool executeCommand(std::vector<std::vector<std::string>>
								p_command);
		std::vector<std::string> parseSeg(std::string target);
		std::vector<std::vector<std::string>> parse(std::string 
								p_statment);
		virtual ~Interface();
};
#endif

