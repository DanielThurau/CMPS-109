#include "Fact.h"

Fact::Fact(const std::string& p_factName, const std::string& p_p1, const std::string& p_p2){
	factName = p_factName;
	p1 = p_p1;
	p2 = p_p2;
}

std::string Fact::getFactName(){
	return factName;
}		

std::string Fact::getP1(){
	return p1;
}

std::string Fact::getP2(){
	return p2;
}
