/* Rule.h */
#include "../common.h"

class Rule{
	private:
		/* ruleName($X, $Y):-ruleOperator factName1($X, $Y) factName2($x, $Y) */
		std::string ruleName;
		std::string factName1;
		std::string factName2;
		std::string ruleOperator;
	public:
		Rule(const std::string& p_ruleName, const std::string& p_ruleOperator, const std::string& p_factName1, const std::string& p_factName2);
		/* Getter methods */
		std::string getRuleName();
		std::string getFactName1();
		std::string getFactName2();
		std::string getOperator();
		~Rule();
};