CC = g++
CFLAGS = -Wall

bin/SimpleComputer: build/main.o build/mySimpleComputer.o build/utility.o build/myTerm.o build/myBigChars.o build/myReadKey.o build/mySignal.o build/CPU.o bin
	$(CC) $(CFLAGS) build/main.o build/mySimpleComputer.o build/utility.o build/myTerm.o build/myBigChars.o build/myReadKey.o build/mySignal.o build/CPU.o -o bin/SimpleComputer 

build/main.o: src/main.cpp src/Header.h build
	$(CC) $(CFLAGS) -c src/main.cpp -o build/main.o

build/mySimpleComputer.o: src/mySimpleComputer.cpp src/Header.h build
	$(CC) $(CFLAGS) -c  src/mySimpleComputer.cpp -o build/mySimpleComputer.o

build/utility.o: src/utility.cpp src/Header.h build
	$(CC) $(CFLAGS) -c  src/utility.cpp -o build/utility.o

build/myTerm.o: src/myTerm.cpp src/Header.h build
	$(CC) $(CFLAGS) -c src/myTerm.cpp -o build/myTerm.o

build/myBigChars.o: src/myBigChars.cpp src/Header.h build
	$(CC) $(CFLAGS) -c src/myBigChars.cpp -o build/myBigChars.o

build/myReadKey.o: src/myReadKey.cpp src/Header.h build
	$(CC) $(CFLAGS) -c src/myReadKey.cpp -o build/myReadKey.o

build/mySignal.o: src/mySignal.cpp src/Header.h build
	$(CC) $(CFLAGS) -c src/mySignal.cpp -o build/mySignal.o

build/CPU.o: src/CPU.cpp src/Header.h build
	$(CC) $(CFLAGS) -c src/CPU.cpp -o build/CPU.o

build:
	mkdir build

bin:
	mkdir bin

clean:
	rm -rf build bin
