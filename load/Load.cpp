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
		while(std::getline(file, line)){
			if(!sri->parse(line)){
				break;
			}
		}
		return true;
	} else {
		std::cout << "Error opening file" << std::endl;
		return false;
	}
}

Interface * Load::startSri() {
	Interface * sri = new Interface();
	return sri;
}

Load::~Load() {

}