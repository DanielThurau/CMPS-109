/* Fact.h */
#include "../common.h"
#include "../base/KnowledgeBase.h"
#include "../base/RuleBase.h"

class Streamer{
	
	protected:
		KnowledgeBase * KB;
		RuleBase * RB;
		std::string pathName; 

	public:
		Streamer(std::string p_pathName, KnowledgeBase * p_KB, RuleBase * p_RB);
		Streamer(std::string p_pathName);



		virtual bool process() = 0;

		~Streamer(); 
}