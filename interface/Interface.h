/* Interface.h */
#include "../common.h"
#include "../base/KnowledgeBase.h"
#include "../base/RuleBase.h"
#include "../inference/Inference.h"
#ifndef INTERFACE_H
#define INTERFACE_H



class Load;
class Dump;

using namespace std;

class Interface {
	private: 
		// parser helper method
		std::vector<std::string> parseSeg(std::string target);
	public: 
		// Pointers to kb and rb
		KnowledgeBase * KB;
		RuleBase * RB;
		// interface constructor 
		Interface();
		// looping command line for user
		void commandLine();
		// takes in a formatted statment and excutes it
		bool executeCommand(std::vector<std::vector<std::string>> p_command);
		// parser for user input
		bool parse(std::string p_statement);
		
};
#endif

