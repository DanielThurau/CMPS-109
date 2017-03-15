#include "../headers/Interface.h"
// #include "../headers/Load.h"
// #include "../headers/Dump.h"
#include <cstring>
#include <string>


//default constructor just creates new objects
Interface::Interface(){
	std::cout << "Please enter my address:";
	std::string p_address;
	std::cin >> p_address;
	const char * p_address_char = p_address.c_str();

	std::cout << "Please enter the port of the server:";
	int p_port;
	std::cin >> p_port;

	mySocket = new TCPSocket(p_address_char, (int)p_port);

	// std::cout << "Server addr: " << mySocket->getRemoteAddress() << '\n';  // Selector returning remote IP address
 //    std::cout << "Cleint addr: " << mySocket->getMyAddress() << '\n';      // Selector returning local IP address
}







void Interface::commandLine(){
	

	
	
	while(1){
		
		std::string statement;
		std::getline(std::cin, statement);
		
		if(statement.length() > 0){
			std::cout << statement << "\n";

			const char * p_statement = statement.c_str();
			std::cout << "p_statement: ";
			std::cout << p_statement << "\n";
			mySocket->writeToSocket(p_statement, 50);
			if (statement == "x") {
			delete(mySocket);
			break;
		}
		}
		std::cout << "SRI Session:";
	}
	
}

Interface::~Interface(){
	
}

