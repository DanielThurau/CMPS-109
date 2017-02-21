/* KnowledgeBase.cpp */
#include "KnowledgeBase.h"

/*
 * Default constructor of KnowledgeBase.  Used when 
 * creating an empty KnowledgBase.
 */
KnowledgeBase::KnowledgeBase(){
	std::cout << "Im in the default constuctor\n";
	size = 0;
}


/*
 * Parameterized Default constructor
 * Used when a KnowledgeBase is substantiated
 * with pre-condifgured data
 */
KnowledgeBase::KnowledgeBase(std::vector<Fact*> p_items){
	std::cout << "Im in the parameterized constructor \n";
	head = new node;
	head->next = NULL;
	head->fact = p_items[0];
	node * runner = head;
	size++;
	for(int i = 1; i < p_items.size(); ++i){
		node * temp = new node;
		temp->fact = p_items[i];
		temp->next=NULL;
		runner->next = temp;
		runner = runner->next;
		size++;
	}
}



/*
 * Check is a private function used for checking  
 * if two facts are equal.  Pass two pointers
 * and check will return true if equal, false if 
 * not.
 */
bool KnowledgeBase::check(Fact * fact1, Fact * fact2){
	if(fact1->getFactName() == fact2->getFactName()){
		if(fact1->getP1()==fact2->getP1() && fact1->getP2() == fact2->getP2()){
			std::cout << "This fact already exists in the KnwoledgeBase\n";
			return true;
		}
	}
	return false;
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
	/* empty list */
	if(size == 0){
		// Create the head
		head = new node;
		head->next = NULL;
		head->fact = p_item;
		// increase size and return true
		++size;
		return true;
	/* already has entries */
	}else{
		node * runner = head;
		/* check existence in KB */
		if(check(runner->fact, p_item)) return false;
		// List traversal
		while(runner->next != NULL){
			runner = runner->next;
			/* Check existence in KB */
			if(check(runner->fact, p_item)) return false;
		}

		// Now at end of list , create new node and insert
		node * temp = new node;
		temp->next = NULL;
		temp->fact = p_item;
		runner->next = temp;

		// increase size and return success
		++size;
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
	std::vector<Fact*> data;
	if(size<1){
		return data;
	}else{
		node * runner = head;
		while(runner != NULL){
			if(runner->fact->getFactName() == p_name){
				std::cout << "Got fact name\n";
				data.push_back(runner->fact);
			}
			runner = runner->next;
		}
		runner = NULL;
		return data;
	}
}

bool KnowledgeBase::dropContent(const std::string & p_name){
	if(size==0){
		return false;
	}else{
		node * runner = head;
		while(head!=runner){
			if(runner->fact->getFactName() == p_name){
				runner = runner->next;
				head->fact = NULL;
				head->next = NULL;
				head = runner;
				--size;
			}else{
				runner = runner->next;
			}
		}
		while(runner->next != NULL){
			std::cout << "Def broke here\n";
			if(runner->next->fact->getFactName() == p_name){
				node * toSplice = runner->next;
				runner->next = toSplice->next;
				toSplice->fact = NULL;
				toSplice->next = NULL;
				toSplice = NULL;
				--size;
			}else{
				runner = runner->next;
			}
		}
	}
	return false;
}



KnowledgeBase::~KnowledgeBase(){
	node * runner = head;
	while(runner!=NULL){
		head = runner->next;
		runner->fact = NULL;
		runner->next = NULL;
		runner = head;
	}
}

