/* Interface.h */
#include "../common.h"
#include "../base/KnowledgeBase.h"
#include "../base/RuleBase.h"


using namespace std;

class Interface {
	private:
		KnowledgeBase * KB;
		RuleBase * RB;
	public: 
		Interface();
		Interface(KnowledgeBase * p_KB, RuleBase * p_RB);
		void commandLine();
		void executeCommand(std::string p_command);
		std::string parse(std::string p_statment);
		virtual ~Interface();
};
