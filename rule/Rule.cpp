/* Rule.cpp */
#include "Rule.h"

Rule::RuleRule(std::string p_ruleName, \
			std::string p_factName1, std::string p_factName2, \
			std::string p_ruleOperator){
		ruleName = p_ruleName;
		factName1 = p_factName1;
		factName2 = p_factName2;
		ruleOperator = p_ruleOperator;
}

std::string Rule::getRulename(){
	return ruleName;
}

std::string Rule::getFactName1(){
	return factName1;
}

std::string Rule::getFactName2(){
	return factName2;
}

std::string Rule::getOperator(){
	return ruleOperator;
}

Rule::~Rule(){

}