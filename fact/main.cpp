#include "../common.h"
#include "Fact.h"

int main(){
	std::vector<std::string > data = {"Father", "Thoma","Daniel"};
	Fact * test;// = new Fact("Father", "Thoma", "Daniel");
	test = new Fact(data);

	std::cout << test->getFactName() << '\n';
	delete(test);
	return 0;
}
