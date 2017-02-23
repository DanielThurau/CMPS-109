#include "Inference.h"

Inference::Inference(KnowledgeBase * p_KB, RuleBase * p_RB){
	KB = p_KB;
	RB = p_RB;
	std::cout << "Created Interface Object\n";
}

std::set<std::vector<std::string>> Inference::query(std::vector<std::string> p_Inference){
	
	std::set<std::vector<std::string>> dud;
	std::cout << "In the Interface query\n";
	
	// std::set<std::vector<std::string>> rb_results = query_RB(p_Inference);
	// std::set<std::vector<std::string>> kb_results = query_KB(p_Inference);

	// print_query(results, p_Inference);
	

	return dud;
}



std::set<std::vector<std::string>> Inference::query_KB(std::vector<std::string> p_Inference){
	int inferenceSize = p_Inference.size();
	std::set<std::vector<std::string>> results;

	// std::vector<Fact*> data = KB->getContent(p_Inference[0]);

	// for(int i = 0; i < data.size(); ++i){
	// 	if(data[i]->getFact()[0].size() == inferenceSize){
	// 		std::vector<std::string > temp_fact = data[i]->getFact()[0];
	// 		std::vector<std::string > temp;
	// 		for(int j = 0; j < inferenceSize; ++j){
	// 			temp.push_back(temp_fact[j]);
	// 		}
	// 		results.insert(temp);
	// 	}
	// }
	return results;
}

std::set<std::vector<std::string>> Inference::query_RB(std::vector<std::string> p_Inference){
	std::set<std::vector<std::string>> results;

	// std::vector<std::vector<std::string>> rule_data;
	// try{
	// 	std::cout << "In try\n";
	// 	Rule this_rule = RB->getContent(p_Inference[0]);
 // 		rule_data = this_rule.getRule();
	// }catch(ExistenceException e){
	// 	return results;		
	// }


	

	// /* p_Inference : {[rulename][operator][rule Target 1][ruleTarget 2]...[ruleTarget N]} */
	// for (int i = 2; i < rule_data.size(); ++i){
	// 	if(rule_data[1][0]=="AND"){
	// 		if(i==2){
	// 			std::cout << "operator is AND, but getting first result\n";
	// 		}else{
	// 			std::cout << "operator is AND, concating with results of set";
	// 			// results = SET_AND(results, query(p_Inference))
	// 		}
	// 	}else{
	// 		std::cout << "operator is OR\n";
	// 	}
	// }

	
	return results;

}

void Inference::print_query(std::set<std::vector<std::string>> p_set, std::vector<std::string> p_Inference){
	// for(auto it = p_set.begin(); it != p_set.end(); ++it){
	// 	std::vector<std::string > v = *it;
	// 	for(int p = 1 ; p < v.size(); p++){
	// 		if(p == v.size()-1){
	// 			std::cout << p_Inference[p] << ":" << v[p] << " ";
	// 		}else{
	// 			std::cout << p_Inference[p] << ":" << v[p] << ", ";
	// 		}
	// 	}
	// 	std::cout << "\n";
	// }
}


std::set<std::vector<std::string>> Inference::SET_OR(std::set<std::vector<std::string>> A, std::set<std::vector<std::string>> B){
	std::set<std::vector<std::string>> final;

	// for(auto it = A.begin(); it != A.end(); ++it){
	// 	final.insert(*it);
	// }
	// for(auto it = B.begin(); it != B.end(); ++it){
	// 	final.insert(*it);
	// }
	return final;

}


std::set<std::vector<std::string>> Inference::SET_AND(std::set<std::vector<std::string>> A, std::set<std::vector<std::string>> B){
	std::set<std::vector<std::string>> final;

	// for(auto it = A.begin(); it != A.end(); ++it){
	// 	if(B.find(*it) != B.end()){
	// 		final.insert(*it);
	// 	}
	// }
	return final;
}





Inference::~Inference(){
	free(KB);
	free(RB);
}