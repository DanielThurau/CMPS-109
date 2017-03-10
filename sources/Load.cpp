/* Load.cpp */
#include "../headers/Load.h"
#include "../headers/Interface.h"

/*
 * Constructor with string and Interface pointer
 * Parameters passed to constructor of Streamer class
 */
Load::Load(std::string p_pathName, Interface * p_sri):
	Streamer(p_pathName, p_sri) {

}

/*
 * Constructor with only string
 * Parameters passed to constructor of Streamer class
 */
Load::Load(std::string p_pathName):
	Streamer(p_pathName) {

}

/*
 * Method performs entire process of opening file
 * and importing into KB/RB
 */
bool Load::process() {
	// Grabs the path type of the file
	std::string pathCheck = pathName.substr(pathName.rfind("."));
	
	// Errors if incorrect path type
	if(pathCheck != ".sri") {
		std::cout << "Invalid file. Please use a .sri file.\n";
		return false;
	}

	std::ifstream file(pathName);
	if (file.is_open()){
		std::string line;
		while(std::getline(file, line)){
			// Passes each line to SRI parser
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

/*
 * Creates an SRI and preloads it with 
 * KB/RB. Returns the Interface 
 */ 
Interface * Load::startSRI() {
	Interface * ourSRI = new Interface();

	std::ifstream file(pathName);
	if (file.is_open()){
		std::string line;
		while(std::getline(file, line)){
			std::cout << line << "\n";
			if(!ourSRI->parse(line)){
				break;
			}
		}
	} else {
		std::cout << "Error opening file" << std::endl;
	}
	return ourSRI;
}

/*
 * Deconstructor
 * Frees sri pointer
 */
Load::~Load() {
	free(sri);
}