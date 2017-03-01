#include "Interface.h"
#include "../load/Load.h"
#include "../dump/Dump.h"

//RULE GrandFather($X,$Z):- AND Father($X,$Y) Father($Y,$Z)

//default constructor just creates new objects
Interface::Interface(){
	KB = new KnowledgeBase();
	RB = new RuleBase();
}

//transfers pointers
Interface::Interface(KnowledgeBase * p_KB, RuleBase * p_RB){
	KB = p_KB;
	RB = p_RB;

}

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

//tested w/o parser
bool Interface::parse(std::string p_statement){
	std::vector<std::string> result; 
	std::istringstream strinput(p_statement);
	
	// Seperates line into words seperated by whitespace
	// Inserts into vector
	while(strinput){
		std::string next_word;
		strinput >> next_word;
		result.push_back(next_word);
	}

	if(result[0] == "RULE") {
		std::vector<std::vector<std::string>> rule = {{"RULE"}};

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
		if(executeCommand(rule)){
			return true;
		}else{
			return false;
		}
		// Execute command

	} else if (result[0] == "FACT") {
		//cout << "Made it to conditional" << endl;
		std::vector<std::vector<std::string>> fact = {{"FACT"}};

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
		if(executeCommand(fact)){
			return true;
		}else{
			return false;
		}
		// Execute Command
	} else if (result[0] == "INFERENCE") {
		std::vector<std::vector<std::string>> query ={{"INFERENCE"}};

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
		if(executeCommand(query)){
			return true;
		}else{
			return false;
		}
		// Execute Command

	} else if (result[0] == "DROP") {
		std::vector<std::vector<std::string>> drop = {{"DROP"}};
		for(auto &str : result) {
			if(str == "DROP") continue;
			std::vector<std::string> rfName;
			rfName.push_back(str);
			drop.push_back(rfName);
		}

		if(executeCommand(drop)){
			return true;
		}else{
			return false;
		}

	} else if (result[0] == "LOAD") {
		std::vector<std::vector<std::string>> load = {{"LOAD"}};

		for(auto &str : result) {
			if(str == "LOAD") continue;
			std::vector<std::string> fileName;
			fileName.push_back(str);
			//this is what I should have changed
			//used to be drop.push_back
			load.push_back(fileName);
		}
		if(executeCommand(load)){
			return true;
		}else{
			return false;
		}

	} else if (result[0] == "DUMP") {
		std::vector<std::vector<std::string>> dump = {{"DUMP"}};

		std::vector<std::string> outputFile;
		outputFile.push_back(result[1]);
		dump.push_back(outputFile);


		// Return dump vector
		if(executeCommand(dump)){
			return true;
		}else{
			return false;
		}
		// Execute command?
	} else {
		std::cout << "Unkown Command" << std::endl;
	}
}

//basic implementation using dummy input
bool Interface::executeCommand 
(std::vector<std::vector<std::string>> p_command){
	//creates fact object and adds it to KB
	if (p_command[0][0] == "FACT") {
		p_command.erase(p_command.begin());
		Fact * f1 = new Fact(p_command);
		KB->addContent(f1);
		// free(f1);
		return true;
	}
	//creates rule object and adds it to RB
	else if (p_command[0][0] == "RULE") {
		p_command.erase(p_command.begin());
		Rule * r1 = new Rule(p_command);
		RB->addContent(r1);
		// free(r1);
		return true;
	}
	else if (p_command[0][0] == "INFERENCE") {

		


		Inference * infer = new Inference(KB, RB);
		//second arguement taken as query
		std::vector<std::string> q1 = p_command[1];
		//prints out extra $x and $y, don't know why tf it does
		std::vector<std::vector<std::string>> results =  infer->query(q1);

		// delete(infer);
		if(p_command.size() > 2){
			for(int i = 1; i < results[0].size();i++){
				std::vector<std::string> temp;
				temp.push_back(p_command[p_command.size()-2][0]);
				for(int j = 0; j < results.size();j++){
					temp.push_back(results[j][i]);
				}
				std::vector<std::vector<std::string >> v;
				v.push_back(temp);
				Fact * f1 = new Fact(v);
				KB->addContent(f1);
			}
		}
		return true;
	}
	else if (p_command[0][0] == "LOAD") {
		Load * ld = new Load(p_command[1][0], this); //random index i chose for testing
		ld->process();
	}
	else if (p_command[0][0] == "DROP") {
		RB->dropContent(p_command[1][0]);//rand index i chose for test
		KB->dropContent(p_command[1][0]);
		//std::cout << "drop worked" << endl;
	}else if (p_command[0][0] == "DUMP"){
		Dump * dump_obj = new Dump(p_command[1][0], this);
		dump_obj->process();
		// delete(dump_obj);
		return true;
	}
	return false;
}

void Interface::commandLine(){
	//testing code used without parser
	/*
	std::vector<std::string> v1 = {"Father","Thoma", "bob"};
	Fact * test = new Fact(v1);
	*/
	//std::vector<std::vector<std::string>> myvector;
	while(1){
		std::cout << "SRI Session:";
		string statement;
		//just dummy input for now
		std::getline (std::cin, statement);
		//will probably swap out conditionals for something else
		if (statement == "x") {
			break;
		}
		if(parse(statement)){
		}

	}
	std::cout << "Outside of commandLine() loop" << endl;
}

Interface::~Interface(){

}

