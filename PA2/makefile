# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version

OPTFLAGS = -O2

bin/mps	: src/main.o
	$(CC) $(OPTFLAGS) -o bin/mps src/main.o 
src/input_output.o	: src/main.cpp
	$(CC) $(OPTFLAGS) $(CFLAGS) -o src/input_output.o src/main.cpp

clean:
	@rm -f src/*.o 

