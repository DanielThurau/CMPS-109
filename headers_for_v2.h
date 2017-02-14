template <typename A>
class Base{
	private:
		/* this is the rulebase ptr.  its interpreted by the 
		* by each child 
		*/
		A * contents; 
	public:
		Base();
		getContent(std::string name)=0; // abstarct method to be made by each class
		addContent(A* item)=0; // adds content to their base
		dropContent(std::string name)=0;
		virtual ~Base();
}