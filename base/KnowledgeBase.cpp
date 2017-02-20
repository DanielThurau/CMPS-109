/* KnowledgeBase.cpp */
#include "KnowledgeBase.h"


KnowledgeBase::KnowledgeBase(){
	std::cout << "Im in the default constuctor\n";
}

KnowledgeBase::KnowledgeBase(T * p_items){
	std::cout << "Im in the parameterized constructor \n";
}

bool KnowledgeBase::addContent(T* p_items){
	return false;
}
 
T * KnowledgeBase::getContent(const std::string & p_name){
	return NULL;
}

bool KnowledgeBase::dropContent(const std::string & p_name){
	return false;
}



KnowledgeBase::~KnowledgeBase(){

}


// template <typename T>
// class KnowledgeBase: public Base<T> {
// 	public:
// 		KnowledgeBase();
// 		KnowledgeBase(T * p_items);

// 		T * getContent(const std::std::string & p_name);
// 		T * addContent(T * p_item);
// 		T * dropContet(const std::string & p_name);
// 		~KnowledgeBase();

// };

// template <typename T>
// class Base{
// 	private:
// 		struct node {
// 			T * x;
// 			node * next;
// 		}

// 		node * root;
// 	public:
// 		Base();
// 		Base(T * p_items);
// 		virtual T * getContent(const std::string & p_name)=0;
// 		virtual T * addContent(T * p_item)=0;
// 		virtual T * dropContet(const std::string & p_name)=0;
// 		~Base();

// };