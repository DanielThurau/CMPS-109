#include "../headers/common.h"
#include "../headers/Interface.h"
#include "../headers/Load.h"

int main(int argc, char *argv[]){
	Interface * ourSRI;

	if(argc == 1){
		ourSRI = new Interface();
		
	}else if(argc == 2){
		// Load * ld = new Load(argv[1]);
		// ourSRI = ld->startSRI();
	}else{
		std::cout << "Usages: ./SRI [path_to_file]\n";
		return 1;
	}
	
	ourSRI -> listen();
	return 0;
}