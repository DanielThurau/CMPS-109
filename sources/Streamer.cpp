/* Streamer.cpp */

#include "Streamer.h"

/*  
 * Constructor using string and Interface *
 * Simply sets pathname and sri respectively
 */ 
Streamer::Streamer(std::string p_pathName, Interface * p_sri):
	pathName(p_pathName), sri(p_sri) {

}

/*
 * Constructor using only string
 * Simply sets pathname while sri stays as an empty pointer
 */
Streamer::Streamer(std::string p_pathName):
	pathName(p_pathName) {
}

/*
 * Deconstructor frees pointer
 */
Streamer::~Streamer() {
	free(sri);
}