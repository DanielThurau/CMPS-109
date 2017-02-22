#include "Interface.h"


//default constructor just creates new objects
Interface::Interface(){
	KB = new KnowledgeBase();
	RB = new RuleBase();
}

//transfers pointers
Interface::Interface(KnowledgeBase * p_KB, RuleBase * p_RB){
	KB = p_KB;
	RB = p_RB;

}

void Interface::commandLine(){
	//testing code used without parser
	std::vector<std::string> v1 = {"Father","Thoma", "bob"};
	Fact * test = new Fact(v1);
	while(1){
		std::cout << "Looping commandLine()" << endl;
		string statement;
		std::cin >> statement;
		//will probably swap out conditionals for something else
		if (statement == "x") {
			break;
		}
		//manually looking for addcontent w.o parser
		else if (statement == "addcontent") {
			std::cout << "ADDING CONTENT" << endl;
			KB->addContent(test);
		}

	}
	std::cout << "Outside of commandLine() loop" << endl;
}

Interface::~Interface(){

}

