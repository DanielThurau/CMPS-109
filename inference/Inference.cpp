#include "Inference.h"

Inference::Inference(KnowledgeBase * p_KB, RuleBase * p_RB){
	KB = p_KB;
	RB = p_RB;
}

std::set<std::vector<std::string>> Inference::query(std::vector<std::string> p_Inference){
	std::set<std::vector<std::string>> results;
	return results;
}

Inference::~Inference(){
	free(KB);
	free(RB);
}



// class Inference{
// 	private:
// 		RuleBase * RB;
// 		KnowledgeBase * KB;
// 	public:
// 		Inference(KnowledgeBase * KB, RuleBase * RB);
// 		std::set<std::vector<std::string>> query(std::vector<std::string>);
// 		~Inference();
// }