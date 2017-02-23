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
//tested w/o parser
std::vector<std::vector<std::string>> 
Interface::parse(std::string p_statement){
	//manually created 2d vector
	std::vector<std::vector<std::string>> dud;
	dud.resize(5, std::vector<std::string>(3, ""));
	dud[0][0] = "RULE";
	dud[1] = {"Parent","$X","$Y"};
	dud[2][0] = "OR";
	dud[3] = {"Father","$X","$Y"};
	dud[4] = {"Mother","$X","$Y"};
	return dud;
}

//basic implementation using dummy input
bool Interface::executeCommand 
(std::vector<std::vector<std::string>> p_command){
	//creates fact object and adds it to KB
	if (p_command[0][0] == "FACT") {
		std::cout << "FACT command" << endl;
		std::vector<std::vector<std::string>> temp 
			= {{p_command[1][0],p_command[2][0],p_command[3][0]}};
		Fact * f1 = new Fact(temp);
		KB->addContent(f1);
		std::cout << "ADDED FACT CONTENT" << endl;
		free(f1);
		return true;
	}
	//creates rule object and adds it to RB
	else if (p_command[0][0] == "RULE") {
		std::cout << "RULE command" << endl;
		std::vector<std::vector<std::string>> temp 
			= {{p_command[1][0],p_command[2][0],
				p_command[3][0], p_command[4][0]}};
		Rule * r1 = new Rule(temp);
		std::cout << "ADDED RULE CONTENT" << endl;
		RB->addContent(r1);
		free(r1);
		return true;
	}
	return false;
}

void Interface::commandLine(){
	//testing code used without parser
	/*
	std::vector<std::string> v1 = {"Father","Thoma", "bob"};
	Fact * test = new Fact(v1);
	*/
	while(1){
		std::cout << "Looping commandLine()" << endl;
		string statement;
		std::cin >> statement;
		//will probably swap out conditionals for something else
		if (statement == "x") {
			break;
		}
		std::vector<std::vector<std::string>> myvector 
				= parse("test");
		executeCommand(myvector);
		//manually looking for addcontent w.o parser
		/*
		else if (command == "addcontent") {
			std::cout << "ADDING CONTENT" << endl;
			KB->addContent(test);
		}*/

	}
	std::cout << "Outside of commandLine() loop" << endl;
}

Interface::~Interface(){

}

