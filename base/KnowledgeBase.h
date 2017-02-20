/* KnowledgeBase.h */
#include "../common.h"
#include "Base.h"

template <typename T>
class KnowledgeBase: public Base<T> {
	public:
		KnowledgeBase();
		KnowledgeBase(T * p_items);

		T * getContent(const std::std::string & p_name);
		bool addContent(T * p_item);
		bool dropContent(const std::string & p_name);
		~KnowledgeBase();

};

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