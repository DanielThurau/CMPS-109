#include "Inference.h"



/* Constructor */
Inference::Inference(KnowledgeBase * p_KB, RuleBase * p_RB){
	KB = p_KB;
	RB = p_RB;
}


/* 
 * Base query  
 * Takes in a vector of strings to be evaluated 
 * always represented by { Name(Predicate1, ... PredicateN) }
 * flag is defaulted to 1 which prints results
 */
std::vector<std::vector<std::string>> Inference::query(std::vector<std::string> p_Inference, int flag){
	/* results of querying the KB and RB with no repeats */
	std::vector<std::vector<std::string>> results;



	/* Results from a query on the rulebase using p_inference */
	std::vector<std::vector<std::string>> rb_results = query_RB(p_Inference);
	/* Results from a query on the kb using p_inference */
	std::vector<std::vector<std::string>> kb_results = query_KB(p_Inference);
	
	// // Combine the results of the two queries (in case they're 0, or theres duplicates)
	results = SET_OR(rb_results, kb_results);

	// if we're on the bottom of the recursive stack
	// print the results to console
	if(flag){
		print_query(results);
	}

	// return the results upwards.  Recursive part
	return results;
}


// query kb returns a 2d vector.  Each index of the first layer contains a vector with it's 0th 
// elelment being the predicate it belongs to.  The rest of the elements are values that
// are legal.  These values match up with other values in other vectors based on their index 
// ex: {{"$X", "Bob", "Dan"}, {"$Y", "Billy", "Rachel"}}. -> {$X, $Y}, {Bob, Billy}, {Dan, Rachel}
std::vector<std::vector<std::string>> Inference::query_KB(std::vector<std::string> p_Inference){
	// get the size of the inference vector (this is for checking if the fact matches the amount
	// predicates bc of same fact name but different # of predicates)
	int inferenceSize = p_Inference.size();

	// create new packaging array.  This will hold the vectors containing legal values represented
	// by the queries
	std::vector<std::vector<std::string>> data;


	// populating the beginning of that new array with their signifiers
	// This creates the first vectors so when data is found, I can push it into 
	// the vectors.
	for(int i = 1; i < inferenceSize; ++i){
		// WE dont want to put in a signifier if its a paramatarized query
		// i.e: Father(Thoma, $X)
		// for now we just dont insert the signifier, later we wont insert the values if they 
		// arent legalw
		if(p_Inference[i][0]=='$'){
			// create the vector
			std::vector<std::string > temp_vector;
			// insert the signifier
			temp_vector.push_back(p_Inference[i]);
			// add that vector with signinfier into the data vector 
			data.push_back(temp_vector);
		}
	}


	// Okay now that we have the data structure all set up, we want to actually get possible
	// macthes to the query.  Given the name of the p_inference, retrieve a vector of 
	// fact objects that we can check if they match our criteria
	std::vector<Fact*> fact_data = KB->getContent(p_Inference[0]);

	// for every fact in the vector holding the facts
	for(int i = 0; i < fact_data.size(); ++i){



		// facts are 2D vectors with only 1 element in first layer and factname + # of predicatess
		// in second layer.  This if statement enters the first layer and checks that the number of 
		// predicates + fact name = the number of predicates of p_interface + p_interface name, and if w
		// were given a paramatarized inference ( Father(Thoma, $X) ) that the non variable predicate
		// is the correct value, and in the correct place 
		if(fact_data[i]->getFact()[0].size() == inferenceSize && filter(p_Inference, fact_data[i]->getFact()[0])){
			// If it passed that test, create a vectro to hold the data of the fact (eliminating needing)
			// a 2d vector and a fact obj 
			std::vector<std::string > TEMP_FACT = fact_data[i]->getFact()[0];

			// start the iterator past the the fact name, starting on predicate 0
			int iter = 1;
			// j can be different from iter,
			int j = 0;
			// overall we only want to add from the fact, the values that arent paramterized
			// we already passed the test to make sure the fact was the corret size, and had any given
			// predicates in the reight place and had the right values
			// so only adding the number of variable predicates
			while(j < data.size()){
				// IF the predicate value of the inference is variable
				if(p_Inference[iter][0] == '$'){
					// add the temporary facts value for that predicate
					data[j].push_back(TEMP_FACT[iter]);
					// increment the iterator on the inference
					iter++;
					// increment the pointer on the data structure
					j++;
				}else{
					// if its a non-variable predicate, increment
					// the p_inference iterator
					iter++;
				}
			}

		}
	}

	// return all values of that data
	return data;
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



// SET_OR, given 2 unique 2d string vectors, return a single 2D string vector containing only the values of both 2D vectors where their 
// signifiers match. 
// i.e {{$X, Bob, Sally, Frank, Ray}, {$Y, ball, circle, triangle, square}} OR
//     {{$X, Joe, Paul, Ben, Dan}, {$Y, rectanlge, rhombus, sphere, cube}, {$Z, red, blue, green, orange}}
// will concatante to: 
//		{{$X, Bob, Sally, Frank, Ray, Joe, Paul, Ben, Dan}, {$Y, ball, circle, triangle, square, rectangle, rhombus, sphere, cube}}
// with no $Z value
std::vector<std::vector<std::string>> Inference::SET_OR(std::vector<std::vector<std::string>> A, std::vector<std::vector<std::string>> B){
	
	// This is the data strcuture of the returning object
	std::vector<std::vector<std::string>> final;

	// If A is empty (i.e no an empty 2d structre)
	if(A.empty()){
		// And b is not 
		if(!B.empty()){
			// return B, there is nothing to compare too.  All of B is correct
			return B;
		}
	// vice versa
	}else if(B.empty()){
		if(!A.empty()){
			return A;
		}
	}

	// starting at the first vector in A (we dont need to start at the smaller one)
	// because if A[i] doesnt exist in B we dont use it, and if B[i] doesnt exist in A
	// we dont use it. So using either structure is arbirtary
	for(auto it = A.begin(); it != A.end(); it++ ){
		// break out the structure located at the *it loation in A
		std::vector<std::string > temp = *it;
		// iterating through every second layer in B
		for(int i = 0; i < B.size(); i++){
			// if the signifier matches in temps structue and one of B's 2nd layer structure
			// (temp is a second layer structure), then these results can be or'd.
			if(temp[0] == B[i][0]){
				// To keep the index the same we need to set a standard, since the size of the second layer
				// structure is uniform in B (A's can be different, but every second layer strcutre is still
				// the same size) we just need to always add A or B first. Here i choose A.  Every insertion 
				// will have A[i].size() number of values , theb B[i].size() number of values
			 	std::vector<std::string > to_be;
			 	// add the signifier to the vector
			 	to_be.push_back(temp[0]);
			 	// copy all of temp's values into it
			 	for(int j = 1; j < temp.size(); j++){
			 		to_be.push_back(temp[j]);
			 	}
			 	// copy all of B[i]'s values into it
			 	for(int j = 1; j < B[i].size(); j++){
			 		to_be.push_back(B[i][j]);
			 	}
			 	// add it to the final data strcut
			 	final.push_back(to_be);

			}
		}
	}

	// return the now combined 2D struct
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


// Removing duplicates
// Takes in a 2D string vector, and needs to iterate through the entire thing and check for duplicates
// if there is a duplicates it means that every predicate item it has, will be somehwere else.  I only need to
// check one column, but when a match comes up i have to check N amout of predicates.  Maybe I should just make a temp
// vector that once it senses a pssible duplicate (column 0 matches their column 0), copy all of its data into a 
// vector and compare.  Therefore the vector being checked on is already in vector form and will cjust have its dat 
// then copied into the final
std::vector<std::vector<std::string>> Inference::remove_duplicates(std::vector<std::vector<std::string >> data){
	// data struct holding all the non duplicate values
	std::vector<std::vector<std::string>> final;
	// get the size
	int size = data.size();
	// for all the signifiers, add them in order to the final data struct
	for(int i = 0; i < size; i++){
		std::vector<std::string > v;
		v.push_back(data[i][0]);
		final.push_back(v);
	}


	// for every item passed the signifier in column one
	for(int i = 1; i < data[0].size(); ++i){
		// create a 1D string vector
		std::vector<std::string> comparing;
		// copy all of its relevant data to it
		/*
			{{$X, Dan, Paul, Ben, Roj, ray, Paul}, {$Y, sally, rachel, carson, bindi, melissa, rachel}, {$Z, red, green, blue, orange, yellow, purple}}
			will become {Dan, Sally, red} when its the correct turn , so next turn would be {Paul, rachel, green}
		*/
		for(int j = 0; j < data.size();j++){
			comparing.push_back(data[j][i]);
		}
		// set the flag to true.  Will evaluate to false if theres a duplicate later in the list
		bool flag = true;
		// For every value past comparing's point in the list (no need to recheck valuea)
		for(int k = i+1; k < data[0].size(); k++){
			// if the first element's are equal
			if(comparing[0] == data[0][k]){
				// copy all of the values of the possible
				std::vector<std::string> compared_to;
				for(int j = 0; j < data.size();j++){
					compared_to.push_back(data[j][k]);
				}
				// if theyre equal switch the flag
				if(comparing == compared_to){
					flag = false;
				}
			}
		}
		// if there wasnt a copy of the item somewhere later in the list
		// add that to the final
		// if there is a copy later in the list, that copy will be added, not you
		if(flag){
			for(int j = 0; j < final.size();j++){
				final[j].push_back(comparing[j]);
			}
		}
	}
	return final;

}