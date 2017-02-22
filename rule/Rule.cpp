/* Rule.cpp */
#include "Rule.h"

Rule::Rule(std::vector<std::string > p_data){
	data = p_data;
	ruleName = data[0];
}

std::string Rule::getRuleName(){
	return ruleName;
}

std::vector<std::string> Rule::getRule(){
	return data;
}

Rule::~Rule(){

}