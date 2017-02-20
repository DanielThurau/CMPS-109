/* Fact.h */
#include "../common.h"


class Fact {
	private:
		/* factName(p1, p2) */
		std::string factName;
		std::string p1;
		std::string p2;
	public:
		Fact(const std::string& p_factName, const std::string& p_p1, const std::string& p_p2);
		/* Getter methods */
		std::string getFactName(); 		
		std::string getP1();
		std::string getP2();
		~Fact();
};