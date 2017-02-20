#include "../common.h"
#include "Fact.h"

int main(){
	std::string a = "Father";
	std::string b = "Thoma";
	std::string c = "Daniel";
	Fact * test;// = new Fact("Father", "Thoma", "Daniel");
	test = new Fact("Father", "Thoma", "Daniel");

	std::cout << test->getFactName() << '\n';
	std::cout << test->getP1() << '\n';
	std::cout << test->getP2() << '\n';
	delete(test);
	return 0;
}
