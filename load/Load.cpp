/* Load.cpp */
#include "Load.h"

Load::Load(std::string p_pathName, KnowledgeBase * p_KB, RuleBase * p_RB):
	Streamer(p_pathName, p_KB, p_RB) {

}

Load::Load(std::string p_pathName):
	Streamer(p_pathName) {

}

std::vector<std::string> Load::parseSeg(std::string target) {
	std::vector<std::string> segment;
	auto rName = target.substr(0, target.find('('));
	segment.push_back(rName);
	target.erase(0, target.find('(') + 1);
	auto rParams = target.substr(0, target.find(')'));
	size_t pos = 0;
	std::string token;
	while ((pos = rParams.find(',')) != std::string::npos) {
		token = rParams.substr(0,pos);
		segment.push_back(token);
		rParams.erase(0, pos + 1);
	}
	if(!rParams.empty()) segment.push_back(rParams);
	return segment;
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

			if(result[0] == "RULE") {
				std::vector<std::vector<std::string>> rule;
				std::vector<std::string> commandName;
				commandName.push_back("RULE");
				rule.push_back(commandName);

				/*  Step is used to determine where we are
				 	Step 0: command name
				 	Step 1: Rule/Fact Name	
				 	Step 2: Operator			
					Step 3: Rule Targets
				*/
				int step = 0;
				for(auto &str : result) {
					if(step == 0){
						step++;
						continue;
					} else if (step == 1) { // Parses Rule/Fact Name
						rule.push_back(parseSeg(str));
						step++;
					} else if (step == 2) { // Parse Operators
						if(str == "AND" | str == "OR") {
							std::vector<std::string> oper;
							oper.push_back(str);
							rule.push_back(oper);
							step++;
						} else {
							//Throw Error
						}
					}  else { //step == 3 // Parse Targets
						rule.push_back(parseSeg(str));
					}
				}
				// Return rule vector?
				// Execute command

			} else if (result[0] == "FACT") {
				std::vector<std::vector<std::string>> fact;
				std::vector<std::string> commandName;
				commandName.push_back("FACT");
				fact.push_back(commandName);

				int step = 0;
				for(auto &str : result) {
					if(step == 0){
						step++;
						continue;
					} else if (step == 1) { // Parses Rule/Fact Name
						fact.push_back(parseSeg(str));
					}
				}

				// Return fact vector?
				// Execute Command
			} else if (result[0] == "INFERENCE") {
				std::vector<std::vector<std::string>> query;
				std::vector<std::string> commandName;
				commandName.push_back("INFERENCE");
				query.push_back(commandName);

				int step = 0;
				for(auto &str : result) {
					if(step == 0){
						step++;
						continue;
					} else if (step == 1) { // Parses Rule/Fact Name
						query.push_back(parseSeg(str));
						step++;
					} else if (step == 2) {
						std::vector<std::string> resName;
						resName.push_back(str);
						query.push_back(resName);
					}
				}

				// Return query vector
				// Execute Command

			} else if (result[0] == "DROP") {
				std::vector<std::vector<std::string>> drop;
				std::vector<std::string> commandName;
				commandName.push_back("DROP");
				drop.push_back(commandName);

				for(auto &str : result) {
					if(str == "DROP") continue;

					std::vector<std::string> rfName;
					rfName.push_back(str);
					drop.push_back(rfName);
				}

				// Return drop vector
				// Execute Command

			} else if (result[0] == "LOAD") {
				//ADDED DROP SO THAT THERE IS NO SCOPE ERROR
				std::vector<std::vector<std::string>> drop;
				std::vector<std::vector<std::string>> load;
				std::vector<std::string> commandName;
				commandName.push_back("LOAD");
				load.push_back(commandName);

				for(auto &str : result) {
					if(str == "LOAD") continue;

					std::vector<std::string> fileName;
					fileName.push_back(str);
					drop.push_back(fileName);
				}

			} else if (result[0] == "DUMP") {
				std::vector<std::vector<std::string>> dump;
				std::vector<std::string> commandName;
				commandName.push_back("DUMP");
				dump.push_back(commandName);

				std::vector<std::string> outputFile;
				outputFile.push_back(result[1]);
				dump.push_back(outputFile);

				// Return dump vector
				// Execute command
			} else {

				// Unkown command
			}


		}

		return true;
	} else {
		std::cout << "Error opening file" << std::endl;
		return false;
	}
}

Load::~Load() {

}
