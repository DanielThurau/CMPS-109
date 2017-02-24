#include "Interface.h"

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
//tested w/o parser
std::vector<std::vector<std::string>> 
Interface::parse(std::string p_statement){
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
		std::vector<std::vector<std::string>> rule;
		std::vector<std::string> commandName;
		commandName.push_back("RULE");
		rule.push_back(commandName);

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
		return rule;
		// Execute command

	} else if (result[0] == "FACT") {
		std::vector<std::vector<std::string>> fact;
		std::vector<std::string> commandName;
		commandName.push_back("FACT");
		fact.push_back(commandName);

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
		return fact;
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
		return query;
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
		return drop;
		// Execute Command

	} else if (result[0] == "LOAD") {
		//ADDED DROP SO THAT THERE IS NO SCOPE ERROR
		std::vector<std::vector<std::string>> drop;
		std::vector<std::vector<std::string>> load;
		std::vector<std::string> commandName;
		commandName.push_back("LOAD");
		load.push_back(commandName);

		for(auto &str : result) {
			if(str == "LOAD") continue;
			std::vector<std::string> fileName;
			fileName.push_back(str);
			drop.push_back(fileName);
		}

		return load;

	} else if (result[0] == "DUMP") {
		std::vector<std::vector<std::string>> dump;
		std::vector<std::string> commandName;
		commandName.push_back("DUMP");
		dump.push_back(commandName);

		std::vector<std::string> outputFile;
		outputFile.push_back(result[1]);
		dump.push_back(outputFile);

		// Return dump vector
		return dump;
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
		std::cout << "FACT command" << endl;
		std::vector<std::vector<std::string>> temp 
			= {{p_command[1][0],p_command[2][0],p_command[3][0]}};
		Fact * f1 = new Fact(temp);
		KB->addContent(f1);
		std::cout << "ADDED FACT CONTENT" << endl;
		free(f1);
		return true;
	}
	//creates rule object and adds it to RB
	else if (p_command[0][0] == "RULE") {
		std::cout << "RULE command" << endl;
		std::vector<std::vector<std::string>> temp 
			= {{p_command[1][0],p_command[2][0],
				p_command[3][0], p_command[4][0]}};
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
		delete(infer);
	}
	else if (p_command[0][0] == "LOAD") {
		std::cout << "LOAD command" << endl;
		Load ld(p_command[5][0]); //random index i chose for testing
		ld.process();
	}
	else if (p_command[0][0] == "DROP") {
		std::cout << "DROP command" << endl;
		RB->dropContent(p_command[0][1]);//rand index i chose for test
		std::cout << "drop worked" << endl;
	}
	return false;
}

void Interface::commandLine(){
	//testing code used without parser
	/*
	std::vector<std::string> v1 = {"Father","Thoma", "bob"};
	Fact * test = new Fact(v1);
	*/
	while(1){
		std::cout << "Looping commandLine()" << endl;
		string statement;
		//just dummy input for now
		std::cin >> statement;
		//will probably swap out conditionals for something else
		if (statement == "x") {
			break;
		}
		std::vector<std::vector<std::string>> myvector 
				= parse("test");
		executeCommand(myvector);
		//manually looking for addcontent w.o parser
		/*
		else if (command == "addcontent") {
			std::cout << "ADDING CONTENT" << endl;
			KB->addContent(test);
		}*/

	}
	std::cout << "Outside of commandLine() loop" << endl;
}

Interface::~Interface(){

}

