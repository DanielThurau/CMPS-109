#include "common.h"
#include "interface/Interface.h"
#include "load/Load.h"

int main(int argc, char *argv[]){
	Interface * ourSRI;

	if(argc == 1){
		ourSRI = new Interface();
		
	}else if(argc == 2){
		Load * ld = new Load(argv[1]);
		ourSRI = ld->startSRI();
	}else{
		std::cout << "Usages: ./SRI [path_to_file]\n";
		return 1;
	}
	
	ourSRI -> commandLine();
	return 0;
}