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
 * and try to insert it in a vector with the same fact name.
 * Complexity: O(m) where m = the number of similar facts 
 * already in the KB
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
 * Returns a vector of all facts with the factname: p_name
 */ 
std::vector<Fact*> KnowledgeBase::getContent(const std::string & p_name){
	if(data.count(p_name) != 0){
		return data[p_name];
	}
	return std::vector<Fact*>();
		
}

/*
 * dropcontent
 * Checks if p_name is a fact in KB, then calls Fact 
 * destructor on all facts associated with p_name
 * and removes key entry from map.
 */ 
bool KnowledgeBase::dropContent(const std::string & p_name){
	if(data.count(p_name) != 0){
		for(int i = 0; i < data[p_name].size(); ++i){
			data[p_name][i]->~Fact();
		}

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


/*
 * ~KnowledgeBase()
 * Iterates through map and calls fact destructor on all facts
 */
KnowledgeBase::~KnowledgeBase(){
	std::cout << "In destructor\n";
	for ( auto i = data.begin(); i != data.end(); ++i ){
		for(int j = 0; j < i->second.size(); j++){
			i->second[j]->~Fact();
		}
	}
}

