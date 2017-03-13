#include "../headers/Interface.h"
// #include "../headers/Load.h"
// #include "../headers/Dump.h"


//default constructor just creates new objects
Interface::Interface(){
}

/* parse seg takes a block and seperates it into a string vector */
std::vector<std::string> Interface::parseSeg(std::string target) {
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


/* 
 * parse takes in a string and will parse it into readable format.
 * Once it has the type of statement it will format it further and
 * call executeCommand().
 */
std::vector<std::vector<std::string>> Interface::parse(std::string p_statement){

	std::vector<std::string> result; 
	std::istringstream strinput(p_statement);
	
	// Seperates line into words seperated by whitespace
	// Inserts into vector
	while(strinput){
		std::string next_word;
		strinput >> next_word;
		result.push_back(next_word);
	}

	// RULE COMMAND
	if(result[0] == "RULE") {
		std::vector<std::vector<std::string>> rule = {{"RULE"}};
		// create an executable rule
		int step = 0;

		std::string stream;
		for(auto &str : result) {
			if(step == 0){
				step++;
				continue;
			} else if (step == 1) { // Parses Rule/Fact Name
				if(str.find(')') == std::string::npos){
					stream += str;
					continue;
				} else {
					stream += str;
					stream.erase(std::remove(stream.begin(), stream.end(), ' '), stream.end());
					rule.push_back(parseSeg(stream));
					stream = "";
					step++;
				}
			} else if (step == 2) { // Parse Operators
				if(str == "AND" | str == "OR") {
					std::vector<std::string> oper;
					oper.push_back(str);
					rule.push_back(oper);
					step++;
				} else {
					return rule;
				}
			}  else { //step == 3 // Parse Targets
				if(str.find(')') == std::string::npos){
					stream += str;
					continue;
				} else {
					stream += str;
					stream.erase(std::remove(stream.begin(), stream.end(), ' '), stream.end());
					rule.push_back(parseSeg(stream));
					stream = "";
				}
			}
		}
		// rule is now a formatted rule command, execute it and return bool upwards
		return rule;
	// FACT COMMAND
	} else if (result[0] == "FACT") {
		std::vector<std::vector<std::string>> fact = {{"FACT"}};
		// create an executable fact
		int step = 0;
		std::string stream;
		for(auto &str : result) {
			if(step == 0){
				step++;
				continue;
			} else if (step == 1) { // Parses Rule/Fact Name
				if(str.find(')') == std::string::npos){
					stream += str;
					continue;
				} else {
					stream += str;
					stream.erase(std::remove(stream.begin(), stream.end(), ' '), stream.end());
					fact.push_back(parseSeg(stream));
					stream = "";
				}
			}
		}
		// fact is now an executable fact
		return fact;
	// INFERENCE COMMAND
	} else if (result[0] == "INFERENCE") {
		std::vector<std::vector<std::string>> query ={{"INFERENCE"}};
		// inference formatting
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
		// query is now executable
		return query;
	// DROP COMMAND
	} else if (result[0] == "DROP") {
		std::vector<std::vector<std::string>> drop = {{"DROP"}};
		// further formatting
		for(auto &str : result) {
			if(str == "DROP") continue;
			std::vector<std::string> rfName;
			rfName.push_back(str);
			drop.push_back(rfName);
		}
		// execute a drop
		return drop;
	// LOAD COMMAND
	} else if (result[0] == "LOAD") {
		std::vector<std::vector<std::string>> load = {{"LOAD"}};

		// further formatting
		for(auto &str : result) {
			if(str == "LOAD") continue;
			std::vector<std::string> fileName;
			fileName.push_back(str);
			load.push_back(fileName);
		}
		// execute a load
		return load;
	// DUMP COMMAND
	} else if (result[0] == "DUMP") {
		std::vector<std::vector<std::string>> dump = {{"DUMP"}};

		// further formatting
		std::vector<std::string> outputFile;
		outputFile.push_back(result[1]);
		dump.push_back(outputFile);

		return dump;
	} else {
		std::cout << "Unkown Command" << std::endl;
		std::vector<std::vector<std::string>> dud = {{"NULL"}};
		return dud;
	}
}


void Interface::commandLine(){
	while(1){
		std::cout << "SRI Session:";
		string statement;
		std::getline (std::cin, statement);
		if (statement == "x") {
			break;
		}
		if(!parse(statement)){
                std::cout << "Your command didn't work\n";
        }

	}
}

Interface::~Interface(){
}

