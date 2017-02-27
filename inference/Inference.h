#include "../common.h"
#include "../base/KnowledgeBase.h"  /* This includes Fact.h as well */
#include "../base/RuleBase.h"  /* This includes Rule.h as well */

class Inference{
	private:
		RuleBase * RB;
		KnowledgeBase * KB;
		void print_query(std::vector<std::vector<std::string>> p_set);
		std::vector<std::vector<std::string>> SET_OR(std::vector<std::vector<std::string>> A, std::vector<std::vector<std::string>> B);
		std::vector<std::vector<std::string>> SET_AND(std::vector<std::vector<std::string>> A, std::vector<std::vector<std::string>> B);
		std::vector<std::vector<std::string>> remove_duplicates(std::vector<std::vector<std::string >> data);
		bool filter(std::vector<std::string> p_filter, std::vector<std::string > data );
		std::vector<std::string> pull(std::vector<std::vector<std::string>> A, std::vector<std::vector<std::string>> B, std::string value, std::string sig);
	public:
		Inference(KnowledgeBase * p_KB, RuleBase * p_RB);
		std::vector<std::vector<std::string>> query(std::vector<std::string> p_Inference, int flag = 1);
		std::vector<std::vector<std::string>> query_KB(std::vector<std::string> p_Inference);
		std::vector<std::vector<std::string>> query_RB(std::vector<std::string> p_Inference);


		~Inference();
};