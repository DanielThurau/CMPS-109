#include "../common.h"
#include "Rule.h"

int main(){
	Rule * test = new Rule("Parent", "OR", "Father", "Mother");
	std::cout << test->getRuleName() << '\n';
	std::cout << test->getFactName1() << '\n';
	std::cout << test->getFactName2() << '\n';
	std::cout << test->getOperator() << '\n';
	return 0;
}