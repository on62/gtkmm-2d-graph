COMPILE_FLAGS = -Wall -Iinclude $(shell pkg-config gtkmm-3.0 --cflags)
LIBS = $(shell pkg-config gtkmm-3.0 --libs)
BUILD_FLAGS = -no-pie

.PHONY: clean directories

build: main interface graph_area
	g++ $(BUILD_FLAGS) $(LIBS) obj/* -o bin/gtkmm-2d-graph

main: directories
	g++ -c $(COMPILE_FLAGS) src/main.cpp -o obj/main.o

interface: directories
	g++ -c $(COMPILE_FLAGS) src/AppInterface.cpp -o obj/AppInterface.o

graph_area: directories
	g++ -c $(COMPILE_FLAGS) src/GraphArea.cpp -o obj/GraphArea.o

clean:
	rm -rf bin
	rm -rf obj

directories:
	mkdir -p bin
	mkdir -p obj
