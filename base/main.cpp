//main.cpp for testing kb

#include "../common.h"
// #include "../fact/Fact.h"
#include "KnowledgeBase.h"

int main(){



	std::vector<Fact*> data1;


	KnowledgeBase * KB = new KnowledgeBase();


	Fact * test = new Fact("Father", "Thoma", "bob");
	Fact * test2 = new Fact("Mother", "Talitha", "sally");
	Fact * test4 = new Fact("Grandfather", "Robert", "greg");
	Fact * test5 = new Fact("Grandfather", "Robert", "Gabriel");
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



	free(test);
	free(test2);
	free(test4);
	free(test5);

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

	
	// free(test);
	// free(test2);
	// free(test4);
	// free(test5);

	return 0;
}


