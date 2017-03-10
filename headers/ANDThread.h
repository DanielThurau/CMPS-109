#include "../thread/headers/Thread.h"
#include "../common.h"
// #include "Inference.h"
class Inference;
// 
class ANDThread : public Thread {
	private:
		Inference * inferenceObject;
		std::vector<std::string> thisInference;
		std::vector<std::vector<std::string>> data;
		std::vector<std::vector<std::string>> results;
		std::vector<std::vector<std::string>> this_v;
	public:
		ANDThread(Inference * p_infereceObject, std::vector<std::string> p_thisInference, std::vector<std::vector<std::string>> p_results, std::vector<std::vector<std::string>> p_this_v);
		std::vector<std::vector<std::string>> getData();
		virtual void * threadMainBody(void * arg);
		~ANDThread();
};