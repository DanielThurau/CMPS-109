#include "ANDThread.h"
#include "Inference.h"

ANDThread::ANDThread(Inference * p_infereceObject, std::vector<std::string> p_thisInference,std::vector<std::vector<std::string>> p_results, std::vector<std::vector<std::string>> p_this_v){
	inferenceObject = p_infereceObject;
	thisInference = p_thisInference;
	results = p_results;
	this_v = p_this_v;
	std::cout << "I have been created \n";

}



void * ANDThread::threadMainBody(void * arg){
	// std::cout << " In main thread body\n";
	// for(int i = 0; i < thisInference.size();i++){
	// 	std::cout << thisInference[i] << " ";
	// }
	// std::cout << "\n";
	std::vector<std::vector<std::string >> data = inferenceObject->query(thisInference, 0);
	std::cout << "PAssed the query\n";
	if(data.size() > 0){
		// mroe than just the sigs
		if(data[0].size() > 1){
			for(int k = 1; k < data[0].size(); k++){
				for(int y = 0; y < this_v.size()-1; y++){
					for(int yy = 0; yy < results.size();yy++){
						if(this_v[y][0] == results[yy][0]){
							results[yy].push_back(this_v[y][1]);
							break;
						}
					}
				}
				for(int y = 0; y < data.size(); y++){
					for(int yy = 0; yy < results.size();yy++){
						if(data[y][0] == results[yy][0]){
							results[yy].push_back(data[y][k]);
							break;
						}
					}
				}
			}
			
		}
	}

}

std::vector<std::vector<std::string>> ANDThread::getData(){
	return results;
}
ANDThread::~ANDThread(){
	// free(inferenceObject);
}