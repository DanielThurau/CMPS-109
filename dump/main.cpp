/* main.cpp */

#include "../common.h"
#include "Dump.h"

int main() {
	//*************************************************************************
	// Rulebase Creation
	//*************************************************************************
	RuleBase * RB = new RuleBase();

	// // Creating the vector to be pushed in to rule
	std::vector<std::vector<std::string>> v1 = {{"Parent", "$X","$Y"}, {"OR"}, {"Father","$X","$Y"}, {"Mother","$X","$Y"}};
	std::vector<std::vector<std::string>> v2 = {{"Grandfather","$X","$Z"}, {"AND"}, {"Father", "$X","$Y"},{"Father","$Y","$Z"}};
	// std::vector<std::string > v3 = {"Grandmother", "OR", "Parent", "Parent"};
	// std::vector<std::string > v4 = {"Friend", "OR", "Nice", "Cool"};
	// std::vector<std::string > v5 = {"Foe", "AND", "Enemy", "Rival"};

	// // Creating the rule using the data vectors
	Rule * r1 = new Rule(v1);
	Rule * r2 = new Rule(v2);
	// Rule * r3 = new Rule(v3);
	// Rule * r4 = new Rule(v4);
	// Rule * r5 = new Rule(v5);
 

	std::cout << "Adding to Rulebase: " << RB->addContent(r1) << '\n';
	std::cout << "Adding to Rulebase: " << RB->addContent(r2) << '\n';
	// std::cout << "Adding to Rulebase: " << RB->addContent(r3) << '\n';
	// std::cout << "Adding to Rulebase: " << RB->addContent(r4) << '\n';
	// std::cout << "Adding to Rulebase: " << RB->addContent(r5) << '\n';
	


	// //******************************************************************************
	// // KnowledgeBase Creation
	// //******************************************************************************

	KnowledgeBase * KB = new KnowledgeBase();

	std::vector<std::vector<std::string>> v6 = {{"Father", "Thoma", "bob"}};
	std::vector<std::vector<std::string>> v7 = {{"Mother", "Talitha", "sally"}};
	// std::vector<std::vector<std::string>> v7 = {{"Mother", "Thoma", "bob"}};
	std::vector<std::vector<std::string>> v8 = {{"Father", "bob", "josh"}};
	// std::vector<std::vector<std::string>> v8 = {{"Grandfather", "Robert", "Greg"}};
	std::vector<std::vector<std::string>> v9 = {{"Father", "bob", "emma"}};
	std::vector<std::vector<std::string>> v10 = {{"Father", "Thoma", "bob"}};

	Fact * f1 = new Fact(v6);
	Fact * f2 = new Fact(v7);
	Fact * f3 = new Fact(v8);
	Fact * f4 = new Fact(v9);
	Fact * f5 = new Fact(v10);

	std::cout << "Adding to KnowledgeBase: " << KB->addContent(f1) << '\n';
	std::cout << "Adding to KnowledgeBase: " << KB->addContent(f2) << '\n';
	std::cout << "Adding to KnowledgeBase: " << KB->addContent(f3) << '\n';
	std::cout << "Adding to KnowledgeBase: " << KB->addContent(f4) << '\n';
	std::cout << "Adding to KnowledgeBase: " << KB->addContent(f5) << '\n';



	// //*******************************************************************************
	// // Creating Dump object
	// //*******************************************************************************
	Dump * dump = new Dump("dump.sri", KB, RB);
	dump->process();

	return 0;
}