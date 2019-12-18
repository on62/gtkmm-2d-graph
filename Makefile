COMPILE_FLAGS = -Wall -Iinclude $(shell pkg-config gtkmm-3.0 --cflags)
LIBS = $(shell pkg-config gtkmm-3.0 --libs)
BUILD_FLAGS = -no-pie

.PHONY: clean

build: main
	g++ $(BUILD_FLAGS) $(LIBS) obj/* -o bin/gtkmm-2d-graph

main: interface
	g++ -c $(COMPILE_FLAGS) src/main.cpp -o obj/main.o

interface:
	g++ -c $(COMPILE_FLAGS) src/AppInterface.cpp -o obj/AppInterface.o

clean:
	rm bin/*
	rm obj/*
