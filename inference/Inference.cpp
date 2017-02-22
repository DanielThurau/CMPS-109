#include "Inference.h"

Inference::Inference(KnowledgeBase * p_KB, RuleBase * p_RB){
	KB = p_KB;
	RB = p_RB;
	std::cout << "Created Interface Object\n";
}

std::set<std::vector<std::string>> Inference::query(std::vector<std::string> p_Inference){
	int inferenceSize = p_Inference.size();

	std::cout << "In the Interface query\n";
	
	std::set<std::vector<std::string>> results;
	std::vector<Fact*> data = KB->getContent(p_Inference[0]);
	for(int i = 0; i < data.size(); ++i){
		if(data[i]->getFact().size() == inferenceSize){
			std::vector<std::string > temp_fact = data[i]->getFact();
			std::vector<std::string > temp;
			for(int j = 0; j < inferenceSize; ++j){
				temp.push_back(temp_fact[j]);
			}
			results.insert(temp);
		}
	}

	for(auto it = results.begin(); it != results.end(); ++it){
		std::vector<std::string > v = *it;
		for(int p = 1 ; p < v.size(); p++){
			if(p == v.size()-1){
				std::cout << p_Inference[p] << ":" << v[p] << " ";
			}else{
				std::cout << p_Inference[p] << ":" << v[p] << ", ";
			}
		}
		std::cout << "\n";
	}


	return results;
}

Inference::~Inference(){
	free(KB);
	free(RB);
}