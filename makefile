src = main.cpp
obj = main.o

all: main

$(obj):
	g++ -c $(src)

main: $(obj)
	g++ -o $@ $^
