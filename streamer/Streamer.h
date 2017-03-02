
/* Fact.h */
#include "../common.h"
#include "../base/KnowledgeBase.h"
#include "../base/RuleBase.h"
#ifndef STREAMER_H
#define STREAMER_H

class Interface;

class Streamer{
	
	protected:
		Interface * sri;
		std::string pathName; 

	public:
		// Constructor using string and Interface pointer
		Streamer(std::string p_pathName, Interface * p_sri);

		// Constructor only using string
		Streamer(std::string p_pathName);

		// Private virutal method to ensure implementation in children
		virtual bool process() = 0;

		// Virtual deconstructor
		virtual ~Streamer(); 
};
#endif