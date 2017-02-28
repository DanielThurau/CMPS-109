#include "Interface.h"



//RULE Grandfather($X,$Z):- AND Father($X,$Y) Father($Y,$Z)
//RULE Grandfather($X, $Z):- AND Father($X, $Y) Father($Y, $Z)


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
	std::istringstream str_input(p_statement);
	
	// Seperates line into words seperated by whitespace
	// Inserts into vector
	int counter = 0;
	std::string next_word;
	while(str_input >> next_word){
		std::cout <<"|"<<next_word<<"|"<<"\n";
		result.push_back(next_word);
	}

	std::string total;
	for(int i = 1; i < result.size();i++){
		total = total+result[i];
	}


	total.erase(std::remove_if(total.begin(), total.end(), ::isspace), total.end());


	if(result[0] == "RULE") {
		std::vector<std::vector<std::string>> rule = {{"RULE"}};

		/*  Step is used to determine where we are
		 	Step 0: command name
		 	Step 1: Rule/Fact Name	
		 	Step 2: Operator			
			Step 3: Rule Targets
		*/
		// int step = 0;
		// for(auto &str : result) {
		// 	if(step == 0){
		// 		step++;
		// 		continue;
		// 	} else if (step == 1) { // Parses Rule/Fact Name
		// 		rule.push_back(parseSeg(str));
		// 		step++;
		// 	} else if (step == 2) { // Parse Operators
		// 		if(str == "AND" | str == "OR") {
		// 			std::vector<std::string> oper;
		// 			oper.push_back(str);
		// 			rule.push_back(oper);
		// 			step++;
		// 		} else {
		// 			//Throw Error
		// 		}
		// 	}  else { //step == 3 // Parse Targets
				rule.push_back(parseSeg(total));
			// }
		// }
	
		std::cout << "Hoping this rulle pulls through: \n";
		for(int i = 0; i < rule.size(); i++){
			for(int j = 0; j < rule[i].size(); j++){
				std::cout << rule[i][j] << " ";
			}
			std::cout << "\n";
		}



		// Return rule vector?
		return true;
		// Execute command

	} else if (result[0] == "FACT") {
		//cout << "Made it to conditional" << endl;
		std::vector<std::vector<std::string>> fact = {{"FACT"}};

		fact.push_back(parseSeg(total));



		//____change____
		std::cout << "A fact from the parse func: \n";
		for(int p = 0; p < fact.size(); p++){
			for(int l = 0; l < fact[p].size(); l++){
				std::cout << fact[p][l] << " ";
			}
			std::cout << "\n";
		}


		//_____end of change ____

		// Return fact vector?
		// if(executeCommand(fact)){
			return true;
		// }else{
			// return false;
		// }
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
		return true;
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
		return true;
		// Execute Command

	} else if (result[0] == "LOAD") {
		std::vector<std::vector<std::string>> load;
		std::vector<std::string> commandName;
		commandName.push_back("LOAD");
		load.push_back(commandName);
		cout << "result[1]" << result[1] << endl;
		for(auto &str : result) {
			if(str == "LOAD") continue;
			std::vector<std::string> fileName;
			fileName.push_back(str);
			//this is what I should have changed
			//used to be drop.push_back
			load.push_back(fileName);
		}

		return true;

	} else if (result[0] == "DUMP") {
		std::vector<std::vector<std::string>> dump;
		std::vector<std::string> commandName;
		commandName.push_back("DUMP");
		dump.push_back(commandName);

		std::vector<std::string> outputFile;
		outputFile.push_back(result[1]);
		dump.push_back(outputFile);

		// Return dump vector
		return true;
		// Execute command?
	} else {
		std::cout << "Unkown Command" << std::endl;
	}
}



//---------------------------------------------------------------------------------------------
// Dan no tocuh above 
//---------------------------------------------------------------------------------------------




/* 
 *executeCommand 
 * takes in a 2D vector of strings and executes a set of commands 
 * based on the interpretation 
 */ 
bool Interface::executeCommand(std::vector<std::vector<std::string>> p_command){
	//creates fact object and adds it to KB
	if (p_command[0][0] == "FACT") {
		std::cout << "FACT command" << endl;
		std::vector<std::vector<std::string>> temp;
		// {{p_command[1][0],p_command[1][1],p_command[1][2]}};
		Fact * f1 = new Fact(temp);
		KB->addContent(f1);
		std::cout << "ADDED FACT CONTENT" << endl;
		//std::vector<std::vector<std::string>>().swap(temp);
		free(f1);
		return true;
	}
	//creates rule object and adds it to RB
	else if (p_command[0][0] == "RULE") {
		std::cout << "RULE command" << endl;
		std::vector<std::vector<std::string>> temp 
			= {p_command[1],p_command[2],
				p_command[3], p_command[4]};
		Rule * r1 = new Rule(temp);
		std::cout << "ADDED RULE CONTENT" << endl;
		RB->addContent(r1);
		free(r1);
		return true;
	}
	else if (p_command[0][0] == "INFERENCE") {
		Inference * infer = new Inference(KB, RB);
		//second arguement taken as query
		std::vector<std::string> q1 = {p_command[1]};
		//prints out extra $x and $y, don't know why tf it does
		infer->query(q1);
		free(infer);
	}
	else if (p_command[0][0] == "LOAD") {
		std::cout << "LOAD command" << endl;
		Load ld(p_command[1][0]); //random index i chose for testing
		ld.process();
	}
	else if (p_command[0][0] == "DROP") {
		std::cout << "DROP command" << endl;
		RB->dropContent(p_command[1][0]);//rand index i chose for test
		KB->dropContent(p_command[1][0]);
		//std::cout << "drop worked" << endl;
	}
	return false;
}

void Interface::commandLine(){
	while(1){
		std::cout << "SRI Session:";
		string statement;
		//just dummy input for now
		std::getline (std::cin, statement);
		//will probably swap out conditionals for something else
		if (statement == "x") {
			break;
		}else{
			if(parse(statement)){
			}
		}

	}
	std::cout << "Outside of commandLine() loop" << endl;
}

Interface::~Interface(){

}

