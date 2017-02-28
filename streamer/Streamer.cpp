/* Streamer.cpp */

#include "Streamer.h"
// #include "../interface/Interface.h"

Streamer::Streamer(std::string p_pathName, Interface * p_sri):
	pathName(p_pathName), sri(p_sri) {

}

Streamer::Streamer(std::string p_pathName):
	pathName(p_pathName) {
}

Streamer::~Streamer() {
	// delete KB;
	// delete RB;
}