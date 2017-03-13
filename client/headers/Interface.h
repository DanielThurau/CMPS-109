/* Interface.h */
#ifndef INTERFACE_H
#define INTERFACE_H

#include "common.h"
#include "../headers/TCPSocket.h"



// class Load;
// class Dump;

using namespace std;

class Interface {
	private: 
		// parser helper method
		TCPSocket * mySocket;
		
	public: 
		// interface constructor 
		Interface();
		// looping command line for user
		void commandLine();
		// parser for user input
		~Interface();
		
};
#endif

