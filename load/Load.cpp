/* Load.cpp */
#include "Load.h"

Load::Load(std::string p_pathName, KnowledgeBase * p_KB, RuleBase * p_RB):
	Streamer(p_pathName, p_KB, p_RB) {

}

Load::Load(std::string p_pathName):
	Streamer(p_pathName) {

}

bool Load::process() {
	std::ifstream file(pathName);
	if (file.is_open()){
		std::string line;
		while(std::getline(file, line)){
			std::vector<std::string> result; 
			std::istringstream strinput(line);
			
			// Seperates line into words seperated by whitespace
			// Inserts into vector
			while(strinput){
				std::string next_word;
				strinput >> next_word;
				result.push_back(next_word);
			}

			/* Debugging: prints vector
			for(auto &str : result){
				std::cout << str << std::endl;
			}
			*/

			if(result[0] == 'RULE') {
				std::vector<std::vector<string>> rule;
				std::vector<std::string> commandName;
				commandName.push_back('RULE')
				rule.push_back(commandName);

				/*  Step is used to determine where we are
				 	Step 0: command name
				 	Step 1: Rule/Fact Name				
					Step 2: Rule Targets
				*/
				int step = 0;
				for(auto &str : result) {
					if(step == 0){
						step++;
						continue;
					} else if (step == 1) { // Parses Rule/Fact Name
						auto rName = str.substr(0, str.find('('))
						std::cout << rName << endl;
					}

				}

			} else if (result[0] == 'FACT') {

			} else if (result[0] == 'INFERENCE') {

			} else if (result[0] == 'DROP') {

			} else if (result[0] == 'LOAD') {

			} else if (result[0] == 'DUMP') {

			} else {

			}


		}
	} else {
		std::cout << "Error opening file" << std::endl;
	}

}

Load::~Load() {

}
