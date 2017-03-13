#include "../headers/common.h"
#include "../headers/Interface.h"

int main(int argc, char *argv[]){
	Interface * ourSRI;

	if(argc == 1){
		ourSRI = new Interface();
		
	}else if(argc == 2){
	}else{
		std::cout << "Usages: ./SRI [path_to_file]\n";
		return 1;
	}
	
	ourSRI -> commandLine();
	return 0;
}