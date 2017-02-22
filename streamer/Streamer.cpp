/* Streamer.cpp */

#include "Streamer.h"

Streamer::Streamer(std::string p_pathName, KnowledgeBase * p_KB, RuleBase * p_RB):
	pathName(p_pathName), KB(p_KB), RB(p_RB) {

}

Streamer::Streamer(std::string p_pathName):
	pathName(p_pathName) {

	KB = new KnowledgeBase();
	RB = new RuleBase();
}

Streamer::~Streamer() {
	delete KB;
	delete RB;
}