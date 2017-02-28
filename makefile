main: interface/Interface.h interface/Interface.cpp 
	g++ -std=c++11 main.cpp interface/Interface.cpp fact/Fact.cpp rule/Rule.cpp base/KnowledgeBase.cpp base/RuleBase.cpp base/exception/NonExistentEntry.cpp inference/Inference.cpp load/Load.cpp streamer/Streamer.cpp dump/Dump.cpp 
