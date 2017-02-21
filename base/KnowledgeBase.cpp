/* KnowledgeBase.cpp */
#include "KnowledgeBase.h"

/*
 * Default constructor of KnowledgeBase.  Used when 
 * creating an empty KnowledgBase.
 */
KnowledgeBase::KnowledgeBase(){
	std::cout << "Im in the default constuctor\n";
}


/*
 * Parameterized Default constructor
 * Used when a KnowledgeBase is substantiated
 * with pre-condifgured data
 */
KnowledgeBase::KnowledgeBase(std::vector<Fact*> p_items){
	std::cout << "Im in the param default constuctor\n";
	for(int i = 0; i < p_items.size(); ++i){
		addContent(p_items[i]);
	}
}




/* 
 * addContent will take a ptr to a Fact obj
 * and try to insert it at the end of a linked list.
 * It is important to transverse the entire list to 
 * check for duplicates.
 *************************************************
 * For Devs:
 * want to implement a faster search, which means a 
 * better data structure
 * OPTIONS: 
 *   1: Dictionary
 *   2: N-ary tree
 */
bool KnowledgeBase::addContent(Fact * p_item){
	if(data.count(p_item->getFactName()) == 0){
		std::cout << "There are no keys\n";
		data[p_item->getFactName()].push_back(p_item);
		return true;
	}else if(std::find(data[p_item->getFactName()].begin(), data[p_item->getFactName()].end(), p_item) == data[p_item->getFactName()].end()){
		std::cout << "There are keys\n";
		data[p_item->getFactName()].push_back(p_item);
		return true;
	}
	return false;
}


/* 
 * getContent 
 *
 *
 *
 */ 
std::vector<Fact*> KnowledgeBase::getContent(const std::string & p_name){
	if(data.count(p_name) != 0){
		return data[p_name];
	}
	return std::vector<Fact*>();
		
}

bool KnowledgeBase::dropContent(const std::string & p_name){
	if(data.count(p_name) != 0){
		data.erase(p_name);
		if(data.count(p_name) == 0){
			return true;
		}else{
			return false;
		}
	}else{
		std::cout << "Nothing to Drop\n";
		return false;
	}
}



KnowledgeBase::~KnowledgeBase(){
	std::cout << "In destructor\n";
	for ( auto i = data.begin(); i != data.end(); ++i ){
		for(int j = 0; j < i->second.size(); j++){
			i->second[j]->~Fact();
		}
	}
}

