#ifndef ORTHREAD_H
#define ORTHREAD_H



#include "Thread.h"
#include "common.h"
// #include "Inference.h"
class Inference;
// 
class ORThread : public Thread {
	private:
		Inference * inferenceObject;
		std::vector<std::string> thisInference;
		std::vector<std::vector<std::string>> data;
	public:
		ORThread(Inference * p_infereceObject, std::vector<std::string> p_thisInference);
		std::vector<std::vector<std::string>> getData();
		virtual void * threadMainBody(void * arg);
		~ORThread();
};

#endif