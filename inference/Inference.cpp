#include "Inference.h"



/* Constructor */
Inference::Inference(KnowledgeBase * p_KB, RuleBase * p_RB){
	KB = p_KB;
	RB = p_RB;
}


/* Base query */
std::vector<std::vector<std::string>> Inference::query(std::vector<std::string> p_Inference, int flag){
	/* the set to be returned of containing all matching values */
	std::vector<std::vector<std::string>> dud;
	
	/* rb_results is the set of values that are returned IF the inference
	   has the same name as a rule in the rulebase */
	std::vector<std::vector<std::string>> rb_results = query_RB(p_Inference);
	
	/* kb_results is the set of values that are returned IF the inference has
	   the same name as a fact/facts in the knowledgebase */
	std::vector<std::vector<std::string>> kb_results = query_KB(p_Inference);
	
	// if(flag){
	// 	print_query(kb_results);
	// }

	// DUD gets the values from both queries into the rb and kb with no duplicates
	dud = SET_OR(rb_results, kb_results);
	// // if the flag is set, print the results (called at the top of the recusion)
	// std::cout << "This is dud: \n";
	// for(int i = 0; i < dud.size(); ++i){
	// 	for(int j = 0; j < dud[i].size(); ++j){
	// 		std::cout << dud[i][j] << " ";
	// 	}
	// 	std::cout << '\n';
	// }
	if(flag){
		// print the query and give it labels from p_Interface
		print_query(dud);
	}
	// std::cout << "Im breaking here \n";

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
	return TEST_DATA;
}

std::vector<std::vector<std::string>> Inference::query_RB(std::vector<std::string> p_Inference){
	std::vector<std::vector<std::string>> results;

	int inferenceSize = p_Inference.size();
	std::vector<std::vector<std::string>>rule_data;
	try{
		Rule this_rule = RB->getContent(p_Inference[0]);
		rule_data = this_rule.getRule();
	}catch(ExistenceException e){
		return results;
	}

	for(int i = 1; i < rule_data[0].size();i++){
		std::vector<std::string > temp;
		temp.push_back(rule_data[0][i]);
		results.push_back(temp);
	}


	std::vector<std::vector<std::string>> prev;
	for(int i = 2; i < rule_data.size(); ++i){
		if(rule_data[1][0] == "OR"){
			// std::vector<std::vector<std::string>> test = query(rule_data[i], 0);
			std::vector<std::vector<std::string>> test = query(rule_data[i], 0);
			int iter = 0;
			for(int j = 1; j < test.size(); ++j){
				test[iter][0] = rule_data[i][j];
				iter++;
			}
			results = SET_OR(results, test);
		}else{
			std::vector<std::vector<std::string>> test = query(rule_data[i], 0);
			int iter = 0;
			for(int j = 1; j < test.size(); ++j){
				test[iter][0] = rule_data[i][j];
				iter++;
			}
			
			if(i==2){

				prev = SET_OR(prev, test);
			}else{

				prev = SET_AND(prev, test);

			}
			
			
		}
	}
	if(rule_data[1][0] == "AND"){
		results = SET_OR(results, prev);
	}




	



	
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


std::vector<std::vector<std::string>> Inference::SET_OR(std::vector<std::vector<std::string>> A, std::vector<std::vector<std::string>> B){
	std::vector<std::vector<std::string>> final;
	if(A.empty()){
		if(!B.empty()){
			return B;
		}
	}else if(B.empty()){
		if(!A.empty()){
			return A;
		}
	}



	// std::cout << "This is A: \n";
	// for(int i = 0; i < A.size(); ++i){
	// 	for(int j = 0; j < A[i].size(); ++j){
	// 		std::cout << A[i][j] << " ";
	// 	}
	// 	std::cout << '\n';
	// }

	// std::cout << "This is B: \n";
	// for(int i = 0; i < B.size(); ++i){
	// 	for(int j = 0; j < B[i].size(); ++j){
	// 		std::cout << B[i][j] << " ";
	// 	}
	// 	std::cout << '\n';
	// }


	for(auto it = A.begin(); it != A.end(); it++ ){
		std::vector<std::string > temp = *it;
		for(int i = 0; i < B.size(); i++){
			 if(temp[0] == B[i][0]){
			 	std::vector<std::string > to_be;
			 	to_be.push_back(temp[0]);
			 	for(int j = 1; j < temp.size(); j++){
			 		to_be.push_back(temp[j]);
			 	}
			 	for(int j = 1; j < B[i].size(); j++){
			 		to_be.push_back(B[i][j]);
			 	}
			 	final.push_back(to_be);

			 }
		}
	}



	




	// std::cout << "This is final: \n";
	// for(int i = 0; i < final.size(); ++i){
	// 	for(int j = 0; j < final[i].size(); ++j){
	// 		std::cout << final[i][j] << " ";
	// 	}
	// 	std::cout << '\n';
	// }

	// std::cout << "This is B: \n";
	// for(int i = 0; i < B.size(); ++i){
	// 	for(int j = 0; j < B[i].size(); ++j){
	// 		std::cout << B[i][j] << " ";
	// 	}
	// 	std::cout << '\n';
	// }






	return final;

}


std::vector<std::vector<std::string>> Inference::SET_AND(std::vector<std::vector<std::string>> A, std::vector<std::vector<std::string>> B){
	
	std::cout << "This is A: \n";
	for(int i = 0; i < A.size(); ++i){
		for(int j = 0; j < A[i].size(); ++j){
			std::cout << A[i][j] << " ";
		}
		std::cout << '\n';
	}

	std::cout << "This is B: \n";
	for(int i = 0; i < B.size(); ++i){
		for(int j = 0; j < B[i].size(); ++j){
			std::cout << B[i][j] << " ";
		}
		std::cout << '\n';
	}



	std::vector<std::vector<std::string>> final;
	for(auto it = A.begin(); it != A.end(); it++ ){
		std::vector<std::string > temp = *it;
		for(int i = 0; i < B.size(); i++){
			 if(temp[0] == B[i][0]){


			 	std::vector<std::string> temp_rule;
			 	std::vector<std::string> v3;
			 	sort(temp.begin(), temp.end());
			 	sort(B[i].begin(), B[i].end());
			 	std::set_intersection(temp.begin(), temp.end(), B[i].begin(), B[i].end(), back_inserter(v3));


			 	std::cout << "TEST AND: \n";
				for(int i = 0; i < v3.size(); i++){
					std::cout << v3[i] << " ";
				}
				std::cout << "\n";

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



// std::vector<std::vector<std::string>> Inference::remove_duplicates(std::vector<std::vector<std::string >> data){
// 	std::vector<std::vector<std::string>> final;
// }