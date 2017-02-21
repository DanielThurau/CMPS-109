/* KnowledgeBase.h */
#include "../common.h"
#include "../fact/Fact.h"
class KnowledgeBase{
	/* Struct to hold our facts */
	private:
		struct node {
			Fact * fact;
			node * next;
		};

		node * head;
		int size;
		/* Internal method */
		bool check(Fact * fact1, Fact * fact2);
	public:
		/* Default constuctor */
		KnowledgeBase();
		/* Paramaterized constructor */
		KnowledgeBase(std::vector<Fact*> p_items);

		/*
		 * public method.  Returns a vector with any
		 * instances of a fact 
		 */
		std::vector<Fact*> getContent(const std::string & p_name);
		
		/*
		 * public method.  Returns a bool on success
		 * of inserting the ptr to the fact obj passed to it
		 */
		bool addContent(Fact * p_item);

		/*
		 * public method.  Returns a bool on success of 
		 * deleting all instances of a fact
		 */
		bool dropContent(const std::string & p_name);
		~KnowledgeBase();

};
