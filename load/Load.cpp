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
	std::string line;
	if (file.is_open()){
		while(std::getline(file, line)){
			std::vector<std::string> result; 
			std::istringstream strinput(line);
			
			while(strinput){
				std::string next_word;
				strinput >> next_word;
				result.push_back(next_word);
			}

			for(auto &str : result){
				std::cout << str << std::endl;
			}
		}
	} else {

	}

}

Load::~Load() {

}
