#include "../common.h"
#include "Interface.h"

int main(){
	/*std::vector<std::vector<std::string>> dud;
        dud.resize(4, std::vector<std::string>(2, ""));
        dud[0] = {"Parent","$X","$Y"};
        dud[1][0] = "AND";
        dud[2] = {"Father","$X","$Y"};
        dud[3] = {"Mother","$X","$Y"};*/
	

	/*RB AND KB CREAETED TO TEST INFERENCE IN INTERFACE.CPP*/
	//vectors for rules
	std::vector<std::vector<std::string>> v1
	 = {{"Parent", "$X","$Y"}, {"AND"}, 
		{"Father","$X","$Y"}, {"Mother","$X","$Y"}};

	std::vector<std::vector<std::string>> v2
	 = {{"Grandfather","$X","$Z"}, {"AND"}, 
		{"Father", "$X","$Y"},{"Father","$Y","$Z"}};

	//rules
	Rule * r1 = new Rule(v1);
	Rule * r2 = new Rule(v2);
	RuleBase * RB = new RuleBase();
	//added rules to RB
	RB->addContent(r1);
	RB->addContent(r2);
	
	
	//vectors for facts
	std::vector<std::vector<std::string>> v3 
			= {{"Father","Thomas","Bob"}};
	std::vector<std::vector<std::string>> v4
			= {{"Mother","Thomas","Bob"}};
	//facts
	Fact * f1 = new Fact(v3);
	Fact * f2 = new Fact(v4);
	KnowledgeBase * KB = new KnowledgeBase();
	//added facts to KB
	KB->addContent(f1);
	KB->addContent(f2);
	
	
	
	//created interface by passing pointers KB and RB
	Interface * ourSRI = new Interface(KB, RB);
	ourSRI->commandLine();
	return 0;
}
