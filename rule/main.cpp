#include "../common.h"
#include "Rule.h"

int main(){
	std::vector<std::string> data1 = {"Parent","$X","$Y","OR","Father","$X","$Y", "Mother","$X","$Y"};
	Rule * test = new Rule(data1);
	std::cout << test->getRuleName() << '\n';
	std::vector<std::string > v = test->getRule();
	// std::cout << test->getFactName2() << '\n';
	// std::cout << test->getOperator() << '\n';
	return 0;
}