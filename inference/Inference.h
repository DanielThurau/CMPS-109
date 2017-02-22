#include "../common.h"
#include "../base/KnowledgeBase.h"
#include "../base/RuleBase.h"

class Inference{
	private:
		RuleBase * RB;
		KnowledgeBase * KB;
	public:
		Inference(KnowledgeBase * p_KB, RuleBase * p_RB);
		std::set<std::vector<std::string>> query(std::vector<std::string>);
		~Inference();
}