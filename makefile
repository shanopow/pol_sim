build:
	g++ -c election_events.cpp -o election_events.o
	g++ -c gov_handler.cpp -o gov_handler.o
	g++ -c main.cpp -o main.o
	g++ election_events.o gov_handler.o main.o -o program.exe