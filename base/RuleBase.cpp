/* RuleBase.cpp */
#include "RuleBase.h"


RuleBase::RuleBase(){

}


RuleBase::RuleBase(std::vector<Rule *> p_items){
	for(int i = 0; i < p_items.size(); ++i){
		addContent(p_items[i]);
	}
}


bool RuleBase::addContent(Rule * p_item){
	std::string ruleName = p_item->getRuleName();
	if(data.count(ruleName) == 0){
		std::cout << "Adding Rule to RB\n";
		data[ruleName] = p_item;
		return true;
	}
	return false;
}

Rule RuleBase::getContent(const std::string & p_name){
	if(data.count(p_name) != 0){
		return *data[p_name];
	}
	throw ExistenceException(p_name);
	// return;
}


bool RuleBase::dropContent(const std::string & p_name){
	if(data.count(p_name) != 0){
		data[p_name]->~Rule();
		data.erase(p_name);
		if(data.count(p_name) == 0){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}


RuleBase::~RuleBase(){
	for ( auto i = data.begin(); i != data.end(); ++i ){
			i->second->~Rule();
	}
}

