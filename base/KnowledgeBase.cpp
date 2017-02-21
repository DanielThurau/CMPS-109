/* KnowledgeBase.cpp */
#include "KnowledgeBase.h"


KnowledgeBase::KnowledgeBase(){
	std::cout << "Im in the default constuctor\n";
	size = 0;
}

KnowledgeBase::KnowledgeBase(Fact * p_items){
	std::cout << "Im in the parameterized constructor \n";
}

bool KnowledgeBase::addContent(Fact * p_item){
	/* empty list */
	if(size == 0){
		head = new node;
		head->next = NULL;
		head->fact = p_item;
		++size;
		return true;
	/* already has entries */
	}else{
		node * runner = head;
		
		while(runner->next != NULL){
			runner = runner->next;
		}
		
		node * temp = new node;
		temp->next = NULL;
		temp->fact = p_item;
		
		runner->next = temp;
		++size;
		return true;
	}
	return false;
}
 
Fact * KnowledgeBase::getContent(const std::string & p_name){
	if(size<1){
		return NULL;
	}else{
		node * runner = head;
		if(runner->fact->getFactName() == p_name){
			std::cout << "Got fact name\n";
			return runner->fact;
		}
		while(runner->next != NULL){
			runner = runner->next;
			if(runner->fact->getFactName() == p_name){
				std::cout << "Got fact name\n";
				return runner->fact;
			}
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
