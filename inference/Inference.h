#include "../common.h"
#include "../base/KnowledgeBase.h"  /* This includes Fact.h as well */
#include "../base/RuleBase.h"  /* This includes Rule.h as well */

class Inference{
	private:
		RuleBase * RB;
		KnowledgeBase * KB;
		void print_query(std::set<std::vector<std::string>> p_set, std::vector<std::string> p_Inference);
		std::set<std::vector<std::string>> SET_OR(std::set<std::vector<std::string>> A, std::set<std::vector<std::string>> B);
		std::set<std::vector<std::string>> SET_AND(std::set<std::vector<std::string>> A, std::set<std::vector<std::string>> B);
	public:
		Inference(KnowledgeBase * p_KB, RuleBase * p_RB);
		std::set<std::vector<std::string>> query(std::vector<std::string> p_Inference);
		std::set<std::vector<std::string>> query_KB(std::vector<std::string> p_Inference);
		std::set<std::vector<std::string>> query_RB(std::vector<std::string> p_Inference);


		~Inference();
};