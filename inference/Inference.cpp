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
	std::set<std::vector<std::string>> rb_results = query_RB(p_Inference);
	
	/* kb_results is the set of values that are returned IF the inference has
	   the same name as a fact/facts in the knowledgebase */
	std::set<std::vector<std::string>> kb_results = query_KB(p_Inference);


	// DUD gets the values from both queries into the rb and kb with no duplicates
	dud = SET_OR(rb_results, kb_results);
	
	// if the flag is set, print the results (called at the top of the recusion)
	if(flag){
		// print the query and give it labels from p_Interface
		print_query(dud, p_Inference);
	}

	// return the set upwards
	return dud;
}


// Query KB returns a set of vectors in the format of {FactName, value1, value2}
std::set<std::vector<std::string>> Inference::query_KB(std::vector<std::string> p_Inference){
	
	// get the size of the inference vector (this is for checking if the fact matches the amount
	// predicates bc of same fact name but different # of predicates)
	int inferenceSize = p_Inference.size();

	// create new packaging array
	std::vector<std::vector<std::string>> TEST_DATA;
	// populating the beginning of that new array with their signifiers
	for(int i = 1; i < inferenceSize; ++i){
		std::cout << p_Inference[i] << '\n';
		if(p_Inference[i][0]=='$'){
			std::vector<std::string > TEMP;
			TEMP.push_back(p_Inference[i]);
			TEST_DATA.push_back(TEMP);
		}
	}




	// creates the set thats going to contain all correct values
	std::set<std::vector<std::string>> results;


	//get the vector of facts from the KB that have the name specified by p_inference (
	// [0] has the name )
	std::vector<Fact*> data = KB->getContent(p_Inference[0]);



	// for every fact in the vector holding the facts
	for(int i = 0; i < data.size(); ++i){

		// facts are 2D vectors with only 1 element in first layer and factname + # of predicatess
		// in second layer.  This if statement enters the first layer and checks that the number of 
		// predicates + fact name = the number of predicates of p_interface + p_interface name
		if(data[i]->getFact()[0].size() == inferenceSize){
			// If it passed that test, create a vectro to hold the data of the fact (eliminating needing)
			// a 2d vector and a fact obj
			std::vector<std::string > temp_fact = data[i]->getFact()[0];
			
			// create an empty vector
			std::vector<std::string > temp;


			// push all the data gotten from the fact into the empty vector
			for(int j = 0; j < inferenceSize; ++j){
				temp.push_back(temp_fact[j]);
			}

			// filter that vector by p_inference and set it equal to the result
			// this will return the naem of the fact and any non-known data 
			// i.e if p_Inference had a known predictae, filter that out
			// this also prunes any facts that dont match a p_inference with a know
			// value (i.e correct fact name for p_inference, but one or all of the predicates isnt
			// correct)
			temp = filter(p_Inference, temp);

			// if the filter didnt erase everything, this has valid data and 
			// should be added to the set
			if(!temp.empty()){
				results.insert(temp);
			}
		}
	}

	// we now have a set that has the name of the fact, and all 
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

	bool pipeline_or_nah = false;
		std::vector<std::string> predicate_test = rule_data[0];
		predicate_test.erase(predicate_test.begin(), predicate_test.begin()+1);
		for(int j = 2; j < rule_data.size(); ++j){
			std::vector<std::string> ruleTargetTest = rule_data[j];
			ruleTargetTest.erase(ruleTargetTest.begin(), ruleTargetTest.begin()+1);
			if(predicate_test != ruleTargetTest){
				pipeline_or_nah = true;
				break;
			}
		} 



	/* p_Inference : {[rulename][operator][rule Target 1][ruleTarget 2]...[ruleTarget N]} */
	for (int i = 2; i < rule_data.size(); ++i){
		if(rule_data[1][0]=="AND"){
			if(pipeline_or_nah){



				std::cout << "Youre a wizard harry \n";






			}else{
				if(i==2){
					results = SET_OR(results, query(rule_data[i], 0));
				}else{
					results = SET_AND(results, query(rule_data[i], 0));
				}
			}



		}else{
			results = SET_OR(results, query(rule_data[i], 0));
		}
	}

	
	return results;
}

void Inference::print_query(std::set<std::vector<std::string>> p_set, std::vector<std::string> p_Inference){
	for(auto it = p_set.begin(); it != p_set.end(); ++it){
		std::vector<std::string > v = *it;

		int i = 1;
		int j = 1;
		while(i < v.size()){
			if(i == v.size()-1 && p_Inference[j][0] == '$'){
				std::cout << p_Inference[j] << ":" << v[i] << " ";
				i++;
				j++;
			}else if(p_Inference[j][0] == '$'){
				std::cout << p_Inference[j] << ":" << v[i] << ", ";
				i++;
				j++;
			}else{
				j++;
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


// std::set<std::vector<std::string>> SET_AND_Pipeline(std::set<std::vector<std::string>> A, std::set<std::vector<std::string>> B){








// }

std::vector<std::string > Inference::filter(std::vector<std::string> p_filter, std::vector<std::string > data ){
	

	auto i = data.begin() + 1;
	int j = 1;
	while(i != data.end()){
		if(p_filter[j][0] == '$'){
			i++;
			j++;
		}else{
			if(*i != p_filter[j]){
				data.erase(data.begin(), data.end());
				return data;
			}else{
				data.erase(i, i+1);
			}
			j++;
		}
	}
	return data;
}


Inference::~Inference(){
	free(KB);
	free(RB);
}