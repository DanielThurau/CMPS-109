/* Fact.h */
#include "../common.h"
#include "../base/KnowledgeBase.h"
#include "../base/RuleBase.h"
#ifndef STREAMER_H
#define STREAMER_H

class Streamer{
	
	protected:
		KnowledgeBase * KB;
		RuleBase * RB;
		std::string pathName; 

	public:
		Streamer(std::string p_pathName, KnowledgeBase * p_KB, RuleBase * p_RB);
		Streamer(std::string p_pathName);



		virtual bool process() = 0;

		virtual ~Streamer(); 
};
#endif
