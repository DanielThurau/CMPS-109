/*
 * Connection.cpp
 * Author: Professor Karim Sobh
 * UCSC
 */
#include "../headers/Connection.h"

//Constructor: Call parent Thread Constructor
Connection::Connection(TCPSocket * p_tcpSocket, Interface * p_threadInterface): Thread(){
	std::cout << "Creating a new connection\n";
	tcpSocket = p_tcpSocket; // Set the TCP socket
	next_connection = NULL; // Set the next pointer to NULL
	threadInterface = p_threadInterface;
}

// A modifier that sets the pointer of the next connection
void Connection::setNextConnection(Connection * connection){
	next_connection = connection;
}

// A Selectot that returned a pointer to the next connection
Connection * Connection::getNextConnection (){
	return next_connection;
}

// Destructor: delete the TCP socket if set
Connection::~Connection(){
	if ( tcpSocket != NULL ) {
		delete (tcpSocket);
	}
}

void * Connection::threadMainBody (void * arg) { // Main thread body for serving the connection
	

	char * buffer_read;
	buffer_read = (char*)calloc(150, sizeof(char));
	while(!tcpSocket->isPeerDisconnected()){
		if(tcpSocket->readFromSocket(buffer_read, 50) == -1){
			std::cout << "Reading from tcpSocket Failed\n";
			tcpSocket->setPeerDisconnected(true);
			break;
		}
		if(strcmp((const char *)buffer_read,"x") == 0){
			tcpSocket->setPeerDisconnected(true);
			break;
		} else if(buffer_read[0]=='D' && buffer_read[1]=='U' && buffer_read[2]=='M' && buffer_read[3] == 'P') {
			std::vector<char*> to_return = threadInterface->grab();
			for(int i = 0; i < to_return.size();i++){
				tcpSocket->writeToSocket((const char *)to_return[i], 1000);
				if(tcpSocket->readFromSocket(buffer_read, 50) == -1){
					std::cout << "Reading from tcpSocket Failed\n";
					tcpSocket->setPeerDisconnected(true);
					break;
				}
				if(strcmp((const char *)buffer_read,"null") != 0){
					break;
				}
			}
		}else{
			char * buffer = (char *)calloc(1000,sizeof(char));
			std::string temp((const char *)buffer_read);
			buffer = threadInterface->parse(temp);
			int buffer_length = 1000;
			if(buffer_length != 0){
				tcpSocket->writeToSocket((const char *)buffer, buffer_length);
				free((char*)buffer);
				buffer_length = 0;
			}
		}
	}

}