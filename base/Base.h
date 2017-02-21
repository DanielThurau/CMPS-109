/* Base.h */
#include "../common.h"


template <typename T>
class Base{
	protected:
		struct node {
			T * x;
			node * next;
		};

		node * root;
		int size;
	public:
		virtual T * getContent()=0;
		virtual bool addContent()=0;
		virtual bool dropContet()=0;
};