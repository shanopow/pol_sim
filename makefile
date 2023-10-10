build:
	g++ -c election_events.cpp -o bin/election_events.o
	g++ -c people.cpp -o bin/people.o
	g++ -c gov_handler.cpp -o bin/gov_handler.o
	g++ -c main.cpp -o bin/main.o
	g++ bin/election_events.o  bin/people.o bin/gov_handler.o bin/main.o -o bin/program.exe

wclean:
	rmdir /s /q bin
	mkdir bin

lclean:
	rm -r bin/*