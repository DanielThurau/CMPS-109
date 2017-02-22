//main.cpp for testing kb

#include "../common.h"
// #include "../fact/Fact.h"
#include "KnowledgeBase.h"

int main(){



	std::vector<Fact*> data1;


	KnowledgeBase * KB = new KnowledgeBase();
	std::vector<std::string> v1 = {"Father", "Thoma", "bob"};
	std::vector<std::string> v2 = {"Mohter", "Talitha", "sally"};
	std::vector<std::string> v3 = {"Grandfather", "Robert", "greg"};
	std::vector<std::string> v4 = {"Grandfather", "Robert", "greg"};

	Fact * test = new Fact(v1);
	Fact * test2 = new Fact(v2);
	Fact * test4 = new Fact(v3);
	Fact * test5 = new Fact(v4);
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
	// for(int i = 0; i < data.size();i++){
	// 	std::cout << data[i]->getP2() << '\n';
	// }



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


	// free(test);
	// free(test2);
	// free(test4);
	// free(test5);

	return 0;
}


