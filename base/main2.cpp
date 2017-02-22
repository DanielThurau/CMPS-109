#include "../common.h"
#include "RuleBase.h"


int main(){

	RuleBase * RB = new RuleBase();

	Rule * test = new Rule("Parent", "OR", "Father", "Mother");
	Rule * test1 = new Rule("Grandfather", "AND", "Parent", "Parent");
	Rule * test2 = new Rule("Grandmother", "OR", "Parent", "Parent");
	Rule * test3 = new Rule("Friend", "OR", "Nice", "Cool");
	Rule * test4 = new Rule("Foe", "AND", "Enemy", "Rival");
	Rule * test5 = new Rule("Foe", "OR", "Enemy", "Rival");

	std::cout << RB->addContent(test) << '\n';
	std::cout << RB->addContent(test1) << '\n';
	std::cout << RB->addContent(test2) << '\n';
	std::cout << RB->addContent(test3) << '\n';
	std::cout << RB->addContent(test4) << '\n';
	std::cout << RB->addContent(test5) << '\n';

	std::cout << "Drop successful: " << RB->dropContent("Parent") << '\n';
	std::cout << "Drop successful: " << RB->dropContent("Parent") << '\n';
	try{
		std::cout << "In try\n";
		Rule test7 = RB->getContent("blank");
	}catch(ExistenceException e){
		std::cout << "Shit broke\n";
	}
	
	// std::cout << test7.getOperator() << '\n';

	return 0;
}


/*
std::vector<Fact*> data1;


	KnowledgeBase * KB = new KnowledgeBase();


	Fact * test = new Fact("Father", "Thoma", "bob");
	Fact * test2 = new Fact("Mother", "Talitha", "sally");
	Fact * test4 = new Fact("Grandfather", "Robert", "greg");
	Fact * test5 = new Fact("Grandfather", "Robert", "martha");
	// data1.push_back(test);
	// data1.push_back(test2);
	// data1.push_back(test4);
	// data1.push_back(test5);

	// KnowledgeBase * KB = new KnowledgeBase(data1);

	std::cout << KB->addContent(test) << '\n';
	std::cout << KB->addContent(test2) << '\n';
	std::cout << KB->addContent(test4) << '\n';
	std::cout << KB->addContent(test5) << '\n';
	std::cout << "Drop successful: " << KB->dropContent("Grandfather") << '\n';
	std::vector<Fact*> data= KB->getContent("Grandfather");
	for(int i = 0; i < data.size();i++){
		std::cout << data[i]->getP2() << '\n';
	}



	// free(test);
	// free(test2);
	// free(test4);
	// free(test5);

	// free(test);
	// free(test2);
	// free(test4);
	// free(test5);
	// // if(test3!=NULL){
	// 	std::cout << test3->getFactName() << '\n';
	// 	std::cout << test3->getP1() << '\n';
	// 	std::cout << test3->getP2() << '\n';
	// }
	delete(KB);
*/