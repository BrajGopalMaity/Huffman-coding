all:
	g++ -std=c++0x -o checkTime checkTime.cpp
	g++ -std=c++0x -o encoder encoder.cpp
	g++ -o decoder decoder.cpp
