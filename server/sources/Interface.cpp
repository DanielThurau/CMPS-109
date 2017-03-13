#include "../headers/Interface.h"
#include "../headers/Load.h"
#include "../headers/Dump.h"


//default constructor just creates new objects
Interface::Interface(){
	KB = new KnowledgeBase();
	RB = new RuleBase();

	std::cout << "Please enter my address:";
	char * p_address;
	std::cin >> p_address;


	std::cout << "Please enter my port:";
	int p_port;
	std::cin >> p_port;

	mySocket = new TCPServerSocket(p_address, (int)p_port, 10);
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

}

Interface::~Interface(){
	delete(KB);
	delete(RB);
}

