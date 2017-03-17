#include "../headers/common.h"
#include "../headers/Interface.h"
#include "../headers/Load.h"
#include "../headers/GarbageCollector.h"
#include "../headers/TCPServerSocket.h"
#include "../headers/Connection.h"
#include <cstring>
#include <string>



int main(int argc, char *argv[]){
	std::cout << "Please enter my address:";
	std::string p_address;
	std::cin >> p_address;
	const char * p_address_char = p_address.c_str();


	std::cout << "Please enter my port:";
	int p_port;
	std::cin >> p_port;


	if(argc == 1){

		TCPServerSocket * tcpServerSocket = new TCPServerSocket(p_address_char, p_port, 100);
		GarbageCollector * garbageCollector = new GarbageCollector();

		tcpServerSocket->initializeSocket();
		for(;;){
			std::cout << "Trying to establish a connection\n";
			TCPSocket * tcpSocket = tcpServerSocket->getConnection();
			if(tcpSocket == NULL){
				std::cout << "That tcpSocket was null\n";
				break;
			}
			garbageCollector->cleanup();
			Interface * inter = new Interface();
			Connection * c = new Connection(tcpSocket, inter);
			c->start();
			garbageCollector->addConnection(c);
		}
		delete(garbageCollector);
		delete(tcpServerSocket);
	}else if(argc == 2){
		// Load * ld = new Load(argv[1]);
		// ourSRI = ld->startSRI();
	}else{
		std::cout << "Usages: ./SRI [path_to_file]\n";
		return 1;
	}
	
	return 0;
}