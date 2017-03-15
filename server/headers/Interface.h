/* Interface.h */
#ifndef INTERFACE_H
#define INTERFACE_H

#include "common.h"
#include "KnowledgeBase.h"
#include "RuleBase.h"
#include "Inference.h"
#include "TCPServerSocket.h"



class Load;
class Dump;

using namespace std;

class Interface {
	private: 
		std::vector<std::string> parseSeg(std::string target);
		std::string format(std::vector<std::vector<std::string>> result);
		std::string formatSize(int size);
		TCPServerSocket * serverSocket;
		char * buffer;

		int buffer_length;
	public: 
		// Pointers to kb and rb
		KnowledgeBase * KB;
		RuleBase * RB;
		// interface constructor 
		Interface();
		// looping command line for user
		void listen();
		// takes in a formatted statment and excutes it
		bool executeCommand(std::vector<std::vector<std::string>> p_command);


		std::string parse(std::string p_statement);
		~Interface();
		
};
#endif

