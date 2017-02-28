
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
		Streamer(std::string p_pathName, Interface * p_sri);
		Streamer(std::string p_pathName);



		virtual bool process() = 0;

		virtual ~Streamer(); 
};
#endif