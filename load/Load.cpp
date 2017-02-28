/* Load.cpp */
#include "Load.h"
#include "../interface/Interface.h"

Load::Load(std::string p_pathName, Interface * p_sri):
	Streamer(p_pathName, p_sri) {

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
<<<<<<< HEAD
			std::vector<std::vector<std::string>> parsedLine = sri->parse(line);
			sri->executeCommand(parsedLine);
=======
			if(!sri->parse(line)){
				break;
			}
>>>>>>> Dan
		}
		return true;
	} else {
		std::cout << "Error opening file" << std::endl;
		return false;
	}
}

<<<<<<< HEAD
Interface * startSri() {
	Interface * sri = new Interface(KB, RB)
=======
Interface * Load::startSri() {
	Interface * sri = new Interface();
>>>>>>> Dan
	return sri;
}

Load::~Load() {

}