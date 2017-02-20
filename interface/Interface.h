#include "../common.h"

/* Interface.h */

using namespace std;

class Interface {
	private:
		KnowledgeBase * KB;
		RuleBase * RB;
	public: 
		Interface();
		Interface(KnowledgeBase * p_KB, RuleBase * RB);
		void commandLine();
		void executeCommand(std::string p_command);
		std::string parse(std::string p_statment)
		virtual ~Interface();
}