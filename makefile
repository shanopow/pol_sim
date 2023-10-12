
build:
	make wclean
	g++ -c src/classlist/election_events.cpp -o bin/election_events.o
	g++ -c src/classlist/ideology.cpp -o bin/ideology.o
	g++ -c src/classlist/people.cpp -o bin/people.o
	g++ -c src/classlist/file_reader.cpp -o bin/file_reader.o
	g++ -c src/classlist/gov_handler.cpp -o bin/gov_handler.o
	g++ -c src/classlist/main.cpp -o bin/main.o
	g++ bin/election_events.o bin/ideology.o bin/file_reader.o bin/people.o bin/gov_handler.o bin/main.o -o bin/program.exe

wclean:
	rmdir /s /q bin
	mkdir bin

lclean:
	rm -r bin/* || make wclean