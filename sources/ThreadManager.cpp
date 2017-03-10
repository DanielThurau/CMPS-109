#include "../headers/ThreadManager.h"
#include "../../inference/Inference.h"
#include "../../inference/ORThread.h"


template <typename T>
ThreadManager<T>::ThreadManager(){
}

template <typename T>
void ThreadManager<T>::addThread(T *p_thread){
	threads.push_back(p_thread);
}

template <typename T>
void ThreadManager<T>::start(){
	// loop on all vector threads and staret them
	int core_id = 0; // core index to set the thread to
	for(int i = 0; i < threads.size();++i){
		threads[i]->start();
		threads[i]->setToCore(core_id); // set it run on the current core_id
		core_id++; // incement cored id for the next thread
		// if core id is equal to the numebr of availle cores reset to 0
		if(core_id == threads[i]->getCoreCount()){
			core_id = 0;
		}
	}
}

template <typename T>
void ThreadManager<T>::barrier(){
	for(int i = 0; i < threads.size(); ++i){
		threads[i]->waitForRunToFinish();
	}
}

template <typename T>
std::vector<std::vector<std::string>> ThreadManager<T>::combineResults(std::vector<std::vector<std::string>> results){

	for(int i = 0; i < threads.size(); i++){
		results = SET_OR(results, threads[i]->getData());
	}
	return results;
}


template <typename T>
ThreadManager<T>::~ThreadManager(){
	for(int i = 0; i < threads.size();i++){
		delete(threads[i]);
	}
}

template<typename T>
std::vector<std::vector<std::string>> ThreadManager<T>::SET_OR(std::vector<std::vector<std::string>> A, std::vector<std::vector<std::string>> B){
	// This is the data strcuture of the returning object
	std::vector<std::vector<std::string>> data;

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
			 	// add it to the data data struct
			 	data.push_back(to_be);

			}
		}
	}
	data = remove_duplicates(data);
	// return the now combined 2D struct
	return data;

}