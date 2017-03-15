#include "../headers/Interface.h"
#include "../headers/Load.h"
#include "../headers/Dump.h"
#include <cstring>
#include <string>

//default constructor just creates new objects
Interface::Interface(){
	KB = new KnowledgeBase();
	RB = new RuleBase();

	std::cout << "Please enter my address:";
	std::string p_address;
	std::cin >> p_address;
	const char * p_address_char = p_address.c_str();


	std::cout << "Please enter my port:";
	int p_port;
	std::cin >> p_port;
	serverSocket = new TCPServerSocket(p_address_char, (int)p_port, 10);
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
					return false;
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
		if(!executeCommand(rule)){
			return false;
		}else{
			return true;
		}
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
		if(!executeCommand(fact)){
			return false;
		}else{
			return true;
		}
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
		if(!executeCommand(query)){
			return false;
		}else{
			return true;
		}
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
		if(!executeCommand(drop)){
			return false;
		}else{
			return true;
		}
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
		if(!executeCommand(load)){
			return false;
		}else{
			return true;
		}
	// DUMP COMMAND
	} else if (result[0] == "DUMP") {
		std::vector<std::vector<std::string>> dump = {{"DUMP"}};

		// further formatting
		std::vector<std::string> outputFile;
		outputFile.push_back(result[1]);
		dump.push_back(outputFile);

		if(!executeCommand(dump)){
			return false;
		}else{
			return true;
		}
	} else {
		std::cout << "Unkown Command" << std::endl;
		return false;
	}
}


//basic implementation using dummy input
bool Interface::executeCommand 
(std::vector<std::vector<std::string>> p_command){
	//creates fact object and adds it to KB
	if (p_command[0][0] == "FACT") {
		// remove indicator 
		p_command.erase(p_command.begin());
		// create new fact and add it
		Fact * f1 = new Fact(p_command);
		KB->addContent(f1);
		return true;
	}
	//creates rule object and adds it to RB
	else if (p_command[0][0] == "RULE") {
		// remove indicator
		p_command.erase(p_command.begin());
		Rule * r1 = new Rule(p_command);
		RB->addContent(r1);
		return true;
	}
	else if (p_command[0][0] == "INFERENCE") {
		// create a new inference object
		Inference * infer = new Inference(KB, RB);
		//second arguement taken as query
		std::vector<std::string> q1 = p_command[1];
		//prints out extra $x and $y, don't know why tf it does
		std::vector<std::vector<std::string>> results =  infer->query(q1);

		// if the user specifies a name to store the results under, store them 
		// in KB

		if(p_command.size() > 3){
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
		// create a load object with this interface and process
		Load * ld = new Load(p_command[1][0], this); 
		if(ld->process()){
			return true;
		}else{
			return false;
		}
	}
	else if (p_command[0][0] == "DROP") {
		// drop from rb and kb 
		RB->dropContent(p_command[1][0]);
		KB->dropContent(p_command[1][0]);
		return true;
	}else if (p_command[0][0] == "DUMP"){
		// create dump obj and call process
		Dump * dump_obj = new Dump(p_command[1][0], this);
		if(dump_obj->process()){
			return true;
		}else{
			return false;
		}
	}
	return false;
}

void Interface::listen(){
	if(!serverSocket->initializeSocket()){
		std::cout << "Initailiztion Failed\n";
		return;
	}
	TCPSocket * clientSocket = serverSocket->getConnection();
	// if(clientSocket->isPeerDisconnected()){
	// 	std::cout << "Connection to Client Failed\n";
	// 	return;
	// }



	char * buffer;
	buffer = (char*)calloc(50, sizeof(char));
	while(!clientSocket->isPeerDisconnected()){
		if(clientSocket->readFromSocket(buffer, 50) == -1){
			std::cout << "Reading from clientSocket Failed\n";
			return;
		}
		// std::cout << "Im broke nhere\n";
		std::cout << "Received from Client Socket: ";

		std::cout << buffer << std::endl;
		parse(buffer);
	}

	delete(clientSocket);







}

Interface::~Interface(){
	delete(KB);
	delete(RB);
	delete(serverSocket);
}

