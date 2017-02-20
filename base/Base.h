/* Base.h */
#include "../common.h"


template <typename T>
class Base{
	private:
		struct node {
			T * x;
			node * next;
		}

		node * root;
		int size;
	public:
		Base();
		Base(T * p_items);
		virtual T * getContent(const std::string & p_name)=0;
		virtual bool addContent(T * p_item)=0;
		virtual bool dropContet(const std::string & p_name)=0;
		~Base();

};