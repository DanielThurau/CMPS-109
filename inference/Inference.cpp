#include "Inference.h"

Inference::Inference(KnowledgeBase * p_KB, RuleBase * p_RB){
	KB = p_KB;
	RB = p_RB;
	std::cout << "Created Interface Object\n";
}

std::set<std::vector<std::string>> Inference::query(std::vector<std::string> p_Inference){
	

	std::cout << "In the Interface query\n";
	
	std::set<std::std::vector<std::string> rb_results = query_RB(p_Inference);
	std::set<std::vector<std::string>> kb_results = query_KB(p_Inference);

	// print_query(results, p_Inference);
	


	return results;
}



std::set<std::vector<std::string>> Inference::query_KB(std::vector<std::string> p_Inference){
	int inferenceSize = p_Inference.size();
	std::set<std::vector<std::string>> results;

	std::vector<Fact*> data = KB->getContent(p_Inference[0]);

	for(int i = 0; i < data.size(); ++i){
		if(data[i]->getFact()[0].size() == inferenceSize){
			std::vector<std::string > temp_fact = data[i]->getFact()[0];
			std::vector<std::string > temp;
			for(int j = 0; j < inferenceSize; ++j){
				temp.push_back(temp_fact[j]);
			}
			results.insert(temp);
		}
	}
	return results;
}

std::set<std::vector<std::string>> Inference::query_RB(std::vector<std::string> p_Inference){
	std::set<std::vector<std::string>> results;
	return results;

}

void Inference::print_query(std::set<std::vector<std::string>> p_set, std::vector<std::string> p_Inference){
	for(auto it = p_set.begin(); it != p_set.end(); ++it){
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
}








Inference::~Inference(){
	free(KB);
	free(RB);
}