/* ANDThread.h */
#ifndef ANDTHREAD_H
#define ANDTHREAD_H

#include "Thread.h"
#include "common.h"
// #include "Inference.h"
class Inference;

class ANDThread : public Thread {
	private:
		// pointer to the inference object calling ANDThread
		Inference * inferenceObject;
		// this is the inference phrase that needs to be queried upon
		std::vector<std::string> thisInference;
		// the set that results of the query will be stored in
		std::vector<std::vector<std::string>> data;
		// data needed from inference to correctly format the results of the query
		std::vector<std::vector<std::string>> results;
		// data needed from inference to correctly format the results of the query
		std::vector<std::vector<std::string>> this_v;
	public:
		
		ANDThread(Inference * p_infereceObject, std::vector<std::string> p_thisInference, std::vector<std::vector<std::string>> p_results, std::vector<std::vector<std::string>> p_this_v);
		std::vector<std::vector<std::string>> getData();
		virtual void * threadMainBody(void * arg);
		~ANDThread();
};

#endif