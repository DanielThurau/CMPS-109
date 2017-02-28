/* dump.cpp */

#include "Dump.h"

Dump::Dump(std::string p_pathName, KnowledgeBase * p_KB, RuleBase * p_RB):
	Streamer(p_pathName, p_KB, p_RB) {

}


bool Dump::process() {
	std::ofstream outFile(pathName);
	if(outFile.is_open()) {
		// Needs some kind of way to retrieve all keys in KB/RB
		// For loop over each key and format to print
		// Nevermind I am going to try to iterate al key value pairs
		std::vector<std::string> kbKeys = KB->getKeys();

		for(auto &key : kbKeys){
			std::vector<Fact*> factVector = KB->getContent(key);

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
				}
				outFile << factString << std::endl;				
			}
		}

		std::vector<std::string> rbKeys = RB->getKeys();

		for(auto &key : rbKeys){
			Rule rule = RB->getContent(key);
			std::string ruleString = "RULE ";
			bool ruleName = true;
			bool isOp = false;
			for(auto &ruleData : rule.getRule()) {
				bool targetName = true;
				for(auto &ruleElement : ruleData) {
					if(targetName) {
						ruleString += ruleElement + "(";
						targetName = false;
					} else if(isOp) {
						ruleString += ruleElement;
					} else {
						ruleString += ruleElement + ",";
					}
				}
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
			std::cout << ruleString << std::endl;
			outFile << ruleString << std::endl;
		}

		outFile.close();
	} else {
		std::cout << "Error opening file\n";
	}
}


Dump::~Dump() {

}