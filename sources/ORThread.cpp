#include "../headers/ORThread.h"
#include "../headers/Inference.h"

ORThread::ORThread(Inference * p_infereceObject, std::vector<std::string> p_thisInference){
	inferenceObject = p_infereceObject;
	thisInference = p_thisInference;
}



void * ORThread::threadMainBody(void * arg){
	data = inferenceObject->query(thisInference, 0);

}

std::vector<std::vector<std::string>> ORThread::getData(){
	return data;
}
ORThread::~ORThread(){
}