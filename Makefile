CC = g++
CFLAGS = -Wall

bin/SimpleComputer: build/SimpleComputer.o build/Source.o build/Utility.o bin
	$(CC) $(CFLAGS) build/SimpleComputer.o build/Source.o build/Utility.o -o bin/SimpleComputer

build/SimpleComputer.o: src/SimpleComputer.cpp src/Header.h build
	$(CC) $(CFLAGS) -c src/SimpleComputer.cpp -o build/SimpleComputer.o

build/Source.o: src/Source.cpp src/Header.h build
	$(CC) $(CFLAGS) -c src/Source.cpp -o build/Source.o

build/Utility.o: src/Utility.cpp src/Header.h build
	$(CC) $(CFLAGS) -c src/Utility.cpp -o build/Utility.o

build:
	mkdir build

bin:
	mkdir bin

clean:
	rm -rf build bin
