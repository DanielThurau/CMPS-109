#include "common.h"
#include "interface/Interface.h"


int main(int argc, char *argv[]){

	Interface * ourSRI = new Interface();
	ourSRI->commandLine();

	return 0;
}