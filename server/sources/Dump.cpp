/* dump.cpp */

#include "../headers/Dump.h"
#include "../headers/Interface.h"

/*
 * Constructor using string and Interface pointer
 * Passes paramaters to Streamer inherited class
 */
Dump::Dump(std::string p_pathName, Interface * p_sri):
	Streamer(p_pathName, p_sri) {

}

/*
 * Performs entire process of dumping all
 * contents of KB/RB to a file
 */
bool Dump::process() {
	// Grabs the path type of the file
	std::string pathCheck = pathName.substr(pathName.rfind("."));
	
	// Errors if incorrect path type
	if(pathCheck != ".sri") {
		std::cout << "Invalid file. Please use a .sri file.\n";
		return false;
	}

	std::ofstream outFile(pathName);
	if(outFile.is_open()) {
		// Retrieves keys from KB
		std::vector<std::string> kbKeys = sri->KB->getKeys();

		// Iterates over each key
		for(auto &key : kbKeys){
			// Grabs fact Vector using key
			std::vector<Fact*> factVector = sri->KB->getContent(key);

			// Iterates through every fact in factVector
			for(auto &fact : factVector){
				std::string factString = "FACT ";
				//Iterates over each vector of the Fact Vector
				bool factName = true;

				for(auto &factData : fact->getFact()) {
					// Iterates over each element in fact
					for(auto &factELement : factData) {
						if(factName) {
							factString += factELement + "(";
							factName = false;
						} else {
							factString += factELement + ",";
						}
					}
					factString.erase(factString.size() - 1);
					factString += ")";
					break;
				}
				outFile << factString << std::endl;				
			}
		}

		// Grabs keys from RB
		std::vector<std::string> rbKeys = sri->RB->getKeys();

		// Iterates over each key
		for(auto &key : rbKeys){
			Rule rule = sri->RB->getContent(key);
			std::string ruleString = "RULE ";
			bool ruleName = true;
			bool isOp = false;
			// Iterates through each data of rule vector
			for(auto &ruleData : rule.getRule()) {
				bool targetName = true;

				// Bandaid fix for empty vector
				if(ruleData[0] == "") {
					break;
				}

				// Iterates through each element of Data
				for(auto &ruleElement : ruleData) {
					if(targetName) {
						ruleString += ruleElement + "(";
						targetName = false;
						continue;
					} else if(isOp) {
						ruleString += ruleElement;
						continue;
					} else {
						ruleString += ruleElement + ",";
						continue;
					}
				}

				// Formatting
				if(ruleName) {
					ruleString.erase(ruleString.size() - 1);
					ruleString += "):- ";
					ruleName = false;
					isOp = true;
				} else if(isOp) {
					ruleString.erase(ruleString.size() - 1);
					ruleString += " ";
					isOp = false;
				} else {
					ruleString.erase(ruleString.size() - 1);
					ruleString += ") ";
				}
			}
			outFile << ruleString << std::endl;
		}

		outFile.close();
		return true;
	} else {
		std::cout << "Error opening file\n";
		return false;
	}
}

/*
 * Deconstructor
 * Frees sri pointer
 */
Dump::~Dump() {
	free(sri);
}