#include "Inference.h"



/* Constructor */
Inference::Inference(KnowledgeBase * p_KB, RuleBase * p_RB){
	KB = p_KB;
	RB = p_RB;
}


/* Base query */
std::set<std::vector<std::string>> Inference::query(std::vector<std::string> p_Inference, int flag){
	
	/* the set to be returned of containing all matching values */
	std::set<std::vector<std::string>> dud;
	
	/* rb_results is the set of values that are returned IF the inference
	   has the same name as a rule in the rulebase */
	// std::set<std::vector<std::string>> rb_results = query_RB(p_Inference);
	
	/* kb_results is the set of values that are returned IF the inference has
	   the same name as a fact/facts in the knowledgebase */
	std::vector<std::vector<std::string>> kb_results = query_KB(p_Inference);
	print_query(kb_results);

	// DUD gets the values from both queries into the rb and kb with no duplicates
	// dud = SET_OR(rb_results, kb_results);
	
	// // if the flag is set, print the results (called at the top of the recusion)
	// if(flag){
	// 	// print the query and give it labels from p_Interface
	// 	print_query(dud, p_Inference);
	// }

	// return the set upwards
	return dud;
}


// Query KB returns a set of vectors in the format of {FactName, value1, value2}
std::vector<std::vector<std::string>> Inference::query_KB(std::vector<std::string> p_Inference){
	// get the size of the inference vector (this is for checking if the fact matches the amount
	// predicates bc of same fact name but different # of predicates)
	int inferenceSize = p_Inference.size();

	// create new packaging array
	std::vector<std::vector<std::string>> TEST_DATA;
	// populating the beginning of that new array with their signifiers
	for(int i = 1; i < inferenceSize; ++i){
		if(p_Inference[i][0]=='$'){
			std::vector<std::string > TEMP;
			TEMP.push_back(p_Inference[i]);
			TEST_DATA.push_back(TEMP);
		}
	}
	std::vector<Fact*> data = KB->getContent(p_Inference[0]);

	// for every fact in the vector holding the facts
	for(int i = 0; i < data.size(); ++i){

		// facts are 2D vectors with only 1 element in first layer and factname + # of predicatess
		// in second layer.  This if statement enters the first layer and checks that the number of 
		// predicates + fact name = the number of predicates of p_interface + p_interface name
		if(data[i]->getFact()[0].size() == inferenceSize && filter(p_Inference, data[i]->getFact()[0])){
			// If it passed that test, create a vectro to hold the data of the fact (eliminating needing)
			// a 2d vector and a fact obj
			std::vector<std::string > TEMP_FACT = data[i]->getFact()[0];

			// start the iterator past the fact name
			int iter = 1;
			int j = 0;
			// ins
			while(j < TEST_DATA.size()){
				if(p_Inference[iter][0] == '$'){
					TEST_DATA[j].push_back(TEMP_FACT[iter]);
					iter++;
					j++;
				}else{
					iter++;
				}
			}

		}
	}



	// std::cout << "This is a test: \n";
	// for(int i = 0; i < TEST_DATA.size(); ++i){
	// 	for(int j = 0; j < TEST_DATA[i].size(); ++j){
	// 		std::cout << TEST_DATA[i][j] << " ";
	// 	}
	// 	std::cout << '\n';
	// }

	// we now have a set that has the name of the fact, and all 
	return TEST_DATA;
}

std::set<std::vector<std::string>> Inference::query_RB(std::vector<std::string> p_Inference){
	std::set<std::vector<std::string>> results;


	
	return results;
}

void Inference::print_query(std::vector<std::vector<std::string>> p_set){
	for(int i = 1; i < p_set[0].size(); ++i){
		for (int j = 0; j < p_set.size(); ++j){
			if(j == p_set.size()-1){
				std::cout << p_set[j][0] << ":" << p_set[j][i];
			}else{
				std::cout << p_set[j][0] << ":" << p_set[j][i] << ", ";
			}
		}
		std::cout << '\n';
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

		test.erase(test.begin(), test.begin()+1);

		for(auto k = B.begin(); k != B.end(); ++k){
			std::vector<std::string> test2 = *k;

			test2.erase(test2.begin(), test2.begin()+1);

			if(test == test2){
				std::vector<std::string > v = *it;
				final.insert(*it);
			} 
		}

	}
	return final;
}

bool Inference::filter(std::vector<std::string> p_filter, std::vector<std::string > data ){
	for(int i = 1; i < p_filter.size(); ++i){
		if(p_filter[i][0] != '$'){
			if(data[i] != p_filter[i]){
				return false;
			}
		}
	}
	return true;
}


Inference::~Inference(){
	free(KB);
	free(RB);
}