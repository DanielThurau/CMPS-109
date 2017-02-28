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
		Interface * sri = startSri();
		while(std::getline(file, line)){
			std::vector<std::vector<std::string>> parsedLine = sri->parse(line);
			sri->executeCommand(parsedLine);
		}
		return true;
	} else {
		std::cout << "Error opening file" << std::endl;
		return false;
	}
}

Interface * startSri() {
	Interface * sri = new Interface(KB, RB)
	return sri;
}

Load::~Load() {

}
