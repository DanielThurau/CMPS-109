/* RuleBase.h */
#include "../common.h"
#include "../rule/Rule.h"
#include "exception/NonExistentEntry.h"

class RuleBase{
	private:
		std::unordered_map< std::string, Rule * > data;
	public:
		RuleBase();
		RuleBase(std::vector<Rule*> p_items);
		Rule getContent(const std::string & p_name);
		bool addContent(Rule * p_item);
		bool dropContent(const std::string & p_name);
		~RuleBase();
};

