//main.cpp for testing kb

#include "../common.h"
// #include "../fact/Fact.h"
#include "Base.h"
#include "KnowledgeBase.h"

int main(){


	KnowledgeBase * KB = new KnowledgeBase();


	Fact * test = new Fact("Father", "Thoma", "Daniel");
	Fact * test2 = new Fact("Mother", "Talitha", "Daniel");
	Fact * test4 = new Fact("Grandfather", "Robert", "Daniel");
	Fact * test5 = new Fact("Grandfather", "Robert", "Gabriel");
	std::cout << KB->addContent(test) << '\n';
	std::cout << KB->addContent(test2) << '\n';
	std::cout << KB->addContent(test4) << '\n';
	std::cout << KB->addContent(test5) << '\n';
	KB->dropContent("Grandfather");
	std::vector<Fact*> data= KB->getContent("Mother");
	for(int i = 0; i < data.size();i++){
		std::cout << data[i]->getP2() << '\n';
	}
	// if(test3!=NULL){
	// 	std::cout << test3->getFactName() << '\n';
	// 	std::cout << test3->getP1() << '\n';
	// 	std::cout << test3->getP2() << '\n';
	// }

	return 0;
}


