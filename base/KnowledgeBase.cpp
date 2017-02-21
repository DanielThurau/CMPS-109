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
KnowledgeBase::KnowledgeBase(Fact * p_items){
	std::cout << "Im in the parameterized constructor \n";
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
Fact * KnowledgeBase::getContent(const std::string & p_name){
	if(size<1){
		return NULL;
	}else{
		node * runner = head;
		while(runner != NULL){
			if(runner->fact->getFactName() == p_name){
				std::cout << "Got fact name\n";
				return runner->fact;
			}
			runner = runner->next;
		}

	}


	return NULL;
}

bool KnowledgeBase::dropContent(const std::string & p_name){
	return false;
}



KnowledgeBase::~KnowledgeBase(){

}



/* KnowledgeBase.h */
// #include "../common.h"
// #include "../fact/Fact.h"
// class KnowledgeBase{
// 	private:
// 		struct node {
// 			Fact * fact;
// 			node * next;
// 		};

// 		node * root;
// 		int size;
// 	public:
// 		KnowledgeBase();
// 		KnowledgeBase(Fact * p_items);
// 		Fact * getContent(const std::string & p_name);
// 		bool addContent(Fact * p_item);
// 		bool dropContent(const std::string & p_name);
// 		~KnowledgeBase();

// };
