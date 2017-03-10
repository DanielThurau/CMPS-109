#include "ORThread.h"
#include "Inference.h"

ORThread::ORThread(Inference * p_infereceObject, std::vector<std::string> p_thisInference){
	inferenceObject = p_infereceObject;
	thisInference = p_thisInference;
	// std::cout << "NEW thread created\n";
	// for(int i = 0; i < p_thisInference.size();i++){
	// 	std::cout << p_thisInference[i] << " ";
	// }
	// std::cout << "\n";
}



void * ORThread::threadMainBody(void * arg){
	// std::cout << " In main thread body\n";
	data = inferenceObject->query(thisInference, 0);
	// std::cout << "I'm some happy data sitting in a tree\n";
	// for(int i = 0; i < data.size();i++){
	// 	for(int j = 0; j < data[i].size();j++){
	// 		std::cout << data[i][j] << " "; 
	// 	}
	// 	std::cout << "\n";
	// }

}

std::vector<std::vector<std::string>> ORThread::getData(){
	return data;
}
ORThread::~ORThread(){
	// free(inferenceObject);
}