#include "../thread/headers/Thread.h"
#include "Inference.h"
class ORThread : public Thread {
	private:
		Inference * inferenceObject;
		std::vector<std::string> thisInference;
	public:
		ORThread(Inference * p_infereceObject, std::vector<std::string> p_thisInference);
		virtual void * threadMainBody(void * arg);
		~ORThread();
};