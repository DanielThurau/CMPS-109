/* Fact.cpp */
#include "Fact.h"

Fact::Fact(std::vector<std::vector<std::string>> p_data){
	data = p_data;
	factName = p_data[0][0];
}

std::string Fact::getFactName(){
	return factName;
}		

std::vector<std::vector<std::string>> Fact::getFact(){
	return data;
}

Fact::~Fact(){}
