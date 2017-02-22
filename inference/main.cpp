#include "../common.h"
#include "Inference.h" /* Include KB and RB which inlcude Fact and Rule */


int main(){




	//*************************************************************************
	// Rulebase Creation
	//*************************************************************************
	RuleBase * RB = new RuleBase();

	// Creating the vector to be pushed in to rule
	std::vector<std::string > v1 = {"Parent", "OR", "Father", "Mother"};
	std::vector<std::string > v2 = {"Grandfather", "AND", "Parent", "Parent"};
	std::vector<std::string > v3 = {"Grandmother", "OR", "Parent", "Parent"};
	std::vector<std::string > v4 = {"Friend", "OR", "Nice", "Cool"};
	std::vector<std::string > v5 = {"Foe", "AND", "Enemy", "Rival"};

	// Creating the rule using the data vectors
	Rule * r1 = new Rule(v1);
	Rule * r2 = new Rule(v2);
	Rule * r3 = new Rule(v3);
	Rule * r4 = new Rule(v4);
	Rule * r5 = new Rule(v5);
 

	std::cout << "Adding to Rulebase: " << RB->addContent(r1) << '\n';
	std::cout << "Adding to Rulebase: " << RB->addContent(r2) << '\n';
	std::cout << "Adding to Rulebase: " << RB->addContent(r3) << '\n';
	std::cout << "Adding to Rulebase: " << RB->addContent(r4) << '\n';
	std::cout << "Adding to Rulebase: " << RB->addContent(r5) << '\n';
	//******************************************************************************

	return 0;
}