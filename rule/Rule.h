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
		Rule(std::string p_ruleName, \
			std::string p_factName1, std::string p_factName2, \
			std::string p_ruleOperator);
		/* Getter methods */
		std::string getRuleName();
		std::string getFactName1();
		std::string getFactName2();
		std::string getOperator();
		~Rule();
};