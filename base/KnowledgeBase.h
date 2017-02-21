/* KnowledgeBase.h */
#include "../common.h"
#include "../fact/Fact.h"
class KnowledgeBase{
	private:
		struct node {
			Fact * fact;
			node * next;
		};

		node * head;
		int size;
	public:
		KnowledgeBase();
		KnowledgeBase(Fact * p_items);
		Fact * getContent(const std::string & p_name);
		bool addContent(Fact * p_item);
		bool dropContent(const std::string & p_name);
		~KnowledgeBase();

};
