all:
	make client
	make server

client: 
	g++ -std=c++11 -pthread client/sources/*.cpp -o clientSRI


server:
	g++ -std=c++11 -pthread server/sources/*.cpp -o serverSRI