#include "Inference.h"

Inference::Inference(KnowledgeBase * p_KB, RuleBase * p_RB){
	KB = p_KB;
	RB = p_RB;
}

std::set<std::vector<std::string>> Inference::query(std::vector<std::string> p_Inference, int flag){
	
	std::set<std::vector<std::string>> dud;
	
	std::set<std::vector<std::string>> rb_results = query_RB(p_Inference);
	std::set<std::vector<std::string>> kb_results = query_KB(p_Inference);

	
	dud = SET_OR(rb_results, kb_results);
	if(flag){
		print_query(dud, p_Inference);
	}
	return dud;
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

	std::vector<std::vector<std::string>> rule_data;
	try{
		Rule this_rule = RB->getContent(p_Inference[0]);
 		rule_data = this_rule.getRule();
 		if(rule_data[0].size() != p_Inference.size()){
 			return results;
 		}
	}catch(ExistenceException e){
		return results;		
	}

	/* p_Inference : {[rulename][operator][rule Target 1][ruleTarget 2]...[ruleTarget N]} */
	for (int i = 2; i < rule_data.size(); ++i){
		if(rule_data[1][0]=="AND"){
			if(i==2){
				std::cout << " Doing the first AND\n";
				results = SET_OR(results, query(rule_data[i], 0));
				print_query(results,p_Inference);
			}else{
				std::cout << "Before and: ";
				print_query(results,p_Inference);
				results = SET_AND(results, query(rule_data[i], 0));
				std::cout << "After and: ";
				print_query(results,p_Inference);
				std::cout << '\n';
				// results = SET_AND(results, query(p_Inference))
			}
		}else{
			results = SET_OR(results, query(rule_data[i], 0));
			std::cout << "operator is OR\n";
		}
	}

	
	return results;
}

void Inference::print_query(std::set<std::vector<std::string>> p_set, std::vector<std::string> p_Inference){
	for(auto it = p_set.begin(); it != p_set.end(); ++it){
		std::vector<std::string > v = *it;
		for(int p = 1; p < v.size(); p++){
			if(p == v.size()-1){
				std::cout << p_Inference[p] << ":" << v[p] << " ";
			}else{
				std::cout << p_Inference[p] << ":" << v[p] << ", ";
			}
		}
		std::cout << "\n";
	}
}


std::set<std::vector<std::string>> Inference::SET_OR(std::set<std::vector<std::string>> A, std::set<std::vector<std::string>> B){
	std::set<std::vector<std::string>> final;

	for(auto it = A.begin(); it != A.end(); ++it){
		final.insert(*it);
	}
	for(auto it = B.begin(); it != B.end(); ++it){
		final.insert(*it);
	}
	return final;

}


std::set<std::vector<std::string>> Inference::SET_AND(std::set<std::vector<std::string>> A, std::set<std::vector<std::string>> B){
	
	std::set<std::vector<std::string>> final;


	for(auto it = A.begin(); it != A.end(); ++it){

		std::vector<std::string> test = *it;

		// std::cout << "Before erase: ";
		// for(int i = 0; i < test.size(); i++){
		// 	std::cout << test[i] << " ";
		// }
		// std::cout << "\n";

		test.erase(test.begin(), test.begin()+1);

		// std::cout << "Before erase: ";
		// for(int i = 0; i < test.size(); i++){
		// 	std::cout << test[i] << " ";
		// }
		// std::cout << "\n";


		// std::cout << "Referenced object: ";
		// for(auto j = it->begin(); j != it->end(); j++){
			
		// 	std::cout << j << "\n";
			
		// }
		// std::cout << "\n";

		for(auto k = B.begin(); k != B.end(); ++k){
			std::vector<std::string> test2 = *k;



			// std::cout << "Before erase: ";
			// for(int i = 0; i < test2.size(); i++){
			// 	std::cout << test2[i] << " ";
			// }
			// std::cout << "\n";

			test2.erase(test2.begin(), test2.begin()+1);

			// std::cout << "Before erase: ";
			// for(int i = 0; i < test2.size(); i++){
			// 	std::cout << test2[i] << " ";
			// }
			// std::cout << "\n";





			if(test == test2){
				std::vector<std::string > v = *it;
				std::cout << "This is a test: ";
				for(int i = 0 ; i < v.size();++i){
					std::cout << v[i] << " ";
				}
				std::cout << '\n';
				final.insert(*it);
			} 
		}

		// if(B.find(*it) != B.end()){




		// 	final.insert(*it);
		// }
	}
	return final;
}





Inference::~Inference(){
	free(KB);
	free(RB);
}